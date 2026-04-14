#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
小红书自动发布脚本 - 服务器无头版
部署在百度智能云 Ubuntu 服务器
"""

import time
import random
import json
import requests
import base64
import logging
from pathlib import Path
from datetime import datetime
from DrissionPage import ChromiumPage, ChromiumOptions

# 配置日志
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - %(levelname)s - %(message)s",
    handlers=[logging.FileHandler("xhs_autopost.log"), logging.StreamHandler()],
)
logger = logging.getLogger(__name__)


class XHSAutoPublisherServer:
    def __init__(self, config_file="config.json"):
        self.config = self.load_config(config_file)
        self.page = None
        self.co = None

    def load_config(self, config_file):
        """加载配置文件"""
        default_config = {
            "openclaw_url": "http://localhost:18789",
            "openclaw_token": None,
            "xiaohongshu_cookies": "xhs_cookies.json",
            "headless": True,  # 服务器必须无头
            "publish_interval": {"min": 300, "max": 600},  # 5-10分钟
            "daily_limit": 3,  # 每天最多发布篇数
            "image_folder": "./images",
            "topics_file": "./topics.txt",
        }

        if Path(config_file).exists():
            with open(config_file, "r", encoding="utf-8") as f:
                return {**default_config, **json.load(f)}
        return default_config

    def init_browser(self):
        """初始化无头浏览器（服务器专用配置）"""
        logger.info("初始化无头浏览器...")

        self.co = ChromiumOptions()

        # 必须的无头配置
        self.co.headless(True)
        self.co.set_argument("--no-sandbox")  # 服务器必需
        self.co.set_argument("--disable-dev-shm-usage")  # 避免内存问题
        self.co.set_argument("--disable-gpu")  # 无头模式不需要 GPU
        self.co.set_argument("--disable-web-security")
        self.co.set_argument("--disable-features=IsolateOrigins,site-per-process")

        # 反检测配置
        self.co.set_argument("--disable-blink-features=AutomationControlled")
        self.co.set_user_agent(
            "Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/120.0.0.0 Safari/537.36"
        )

        # 窗口大小（模拟真实用户）
        self.co.set_argument("--window-size=1920,1080")

        # 语言设置
        self.co.set_argument("--lang=zh-CN")

        # 数据目录（持久化 Cookie）
        user_data_dir = Path.home() / ".xhs_browser_data"
        user_data_dir.mkdir(exist_ok=True)
        self.co.set_user_data_path(str(user_data_dir))

        try:
            self.page = ChromiumPage(addr_or_opts=self.co)
            logger.info("✅ 浏览器初始化完成")
            return True
        except Exception as e:
            logger.error(f"❌ 浏览器启动失败: {e}")
            return False

    def generate_content(self, topic):
        """通过 OpenClaw 生成小红书文案"""
        logger.info(f"正在通过 OpenClaw 生成内容: {topic}")

        # 更严格的 prompt，禁止 AI 添加寒暄
        prompt = f"""你是一位专业的小红书文案创作者。请严格按以下格式输出，不要添加任何解释或寒暄：

【标题】：（20字以内，包含2-3个emoji）
【正文】：（150-300字，分段清晰，包含5-8个话题标签#标签名）

主题：{topic}

要求：
- 语气亲切自然，像真实用户分享
- 避免营销感
- 结尾引导互动
- 只输出【标题】和【正文】两部分，不要有任何其他文字"""

        try:
            headers = {"Content-Type": "application/json"}

            if self.config.get("openclaw_token"):
                headers["Authorization"] = f"Bearer {self.config['openclaw_token']}"

            response = requests.post(
                f"{self.config['openclaw_url']}/v1/chat/completions",
                headers=headers,
                json={
                    "model": "openclaw:main",
                    "messages": [{"role": "user", "content": prompt}],
                    "temperature": 0.7,  # 降低随机性
                    "max_tokens": 600,
                },
                timeout=60,
            )

            if response.status_code != 200:
                logger.error(
                    f"OpenClaw API 错误: {response.status_code} - {response.text}"
                )
                return None, None

            result = response.json()
            content = result["choices"][0]["message"]["content"]

            # 更健壮的解析逻辑
            title, body = self.parse_content_strict(content)

            if not title or not body:
                logger.error("内容解析失败，使用备用方案")
                return self.fallback_content(topic)

            logger.info(f"✅ AI生成完成: {title[:30]}...")
            return title, body

        except Exception as e:
            logger.error(f"❌ AI生成失败: {e}")
            return self.fallback_content(topic)

    def parse_content_strict(self, content):
        """严格解析 AI 返回的内容"""
        title = ""
        body = ""

        # 尝试匹配【标题】格式
        import re

        # 匹配【标题】：(内容) 或 【标题】：(内容)
        title_match = re.search(r"【标题】[：:]?\s*(.+?)(?=\n|$)", content)
        if title_match:
            title = title_match.group(1).strip()

        # 匹配【正文】：(内容)
        body_match = re.search(r"【正文】[：:]?\s*([\s\S]+?)(?=\n【|$)", content)
        if body_match:
            body = body_match.group(1).strip()

        # 如果新格式失败，尝试旧格式（兼容）
        if not title:
            lines = content.strip().split("\n")
            for i, line in enumerate(lines):
                line = line.strip()
                if line.startswith("标题") or line.startswith("【标题】"):
                    title = re.sub(r"[【】\[\]标题：:]", "", line).strip()
                elif line.startswith("正文") or line.startswith("【正文】"):
                    body = "\n".join(lines[i + 1 :]).strip()
                    break

        # 清理
        if title:
            title = title.replace("**", "").replace("#", "").strip()
            # 限制长度
            if len(title) > 20:
                title = title[:20]

        if body:
            body = body.replace("**", "").strip()

        return title, body

    def fallback_content(self, topic):
        """备用内容生成"""
        logger.warning("使用备用模板生成内容")
        title = f"{topic}｜分享日常✨"
        body = f"今天想和大家聊聊{topic}～\n\n这是我自己亲身体验的分享，希望对大家有所帮助！\n\n#{topic.replace(' ', '')} #日常分享 #生活记录"
        return title, body

    def parse_content(self, content):
        """解析 AI 返回的内容"""
        lines = content.strip().split("\n")
        title = ""
        body = ""

        for line in lines:
            line = line.strip()
            if line.startswith("标题：") or line.startswith("标题:"):
                title = line.replace("标题：", "").replace("标题:", "").strip()
            elif line.startswith("正文：") or line.startswith("正文:"):
                body = line.replace("正文：", "").replace("正文:", "").strip()
            elif body or (title and not line.startswith("标题")):
                body += "\n" + line

        # 清理
        title = title.replace("**", "").replace("#", "").strip()
        body = body.replace("**", "").strip()

        # 如果解析失败，使用备用方案
        if not title:
            title = lines[0][:20] if lines else "分享日常"
        if not body:
            body = "\n".join(lines[1:]) if len(lines) > 1 else content

        return title, body

    def login(self):
        """登录小红书（Cookie 或手动）"""
        logger.info("访问小红书...")
        self.page.get("https://www.xiaohongshu.com")
        time.sleep(3)

        cookie_file = self.config["xiaohongshu_cookies"]

        # 尝试 Cookie 登录
        if Path(cookie_file).exists():
            logger.info("尝试 Cookie 登录...")
            with open(cookie_file, "r", encoding="utf-8") as f:
                cookies = json.load(f)
            self.page.set.cookies(cookies)
            self.page.refresh()
            time.sleep(3)

            # 验证登录状态
            if self.check_login_status():
                logger.info("✅ Cookie 登录成功")
                return True
            else:
                logger.warning("⚠️ Cookie 失效，需要重新登录")

        # 服务器无头模式下，Cookie 登录是唯一方式
        # 如果在本地有头模式登录过，把 Cookie 文件上传到服务器
        logger.error("❌ 未找到有效 Cookie，无法登录")
        logger.info("💡 解决方案：在本地电脑登录后，将 xhs_cookies.json 上传到服务器")
        return False

    def check_login_status(self):
        """检查登录状态"""
        try:
            # 检查是否有登录按钮或登录页面特征
            html = self.page.html
            if "登录" in html and "手机号登录" in html:
                return False

            # 检查是否有用户头像或创作中心入口
            if (
                self.page.ele("css:.avatar", timeout=3)
                or self.page.ele("css:.creator-center", timeout=3)
                or "创作中心" in html
            ):
                return True

            return False
        except:
            return False

    def publish_note(self, title, content, image_paths=None):
        """发布笔记 - 修复版"""
        logger.info(f"开始发布: {title[:30]}...")

        try:
            # 1. 访问创作中心（等待页面完全加载）
            self.page.get("https://creator.xiaohongshu.com/publish/publish")

            # 等待页面加载（检查关键元素）
            logger.info("等待页面加载...")
            time.sleep(5)  # 给足加载时间

            # 保存截图用于调试
            self.save_screenshot("1_publish_page_loaded.png")

            # 2. 上传图片（如果有）
            if image_paths and len(image_paths) > 0:
                self.upload_images_v2(image_paths)

            # 3. 填写标题
            if not self.fill_title_v2(title):
                logger.error("填写标题失败，中止发布")
                return False

            # 4. 填写正文
            if not self.fill_content_v2(content):
                logger.error("填写正文失败，中止发布")
                return False

            # 5. 模拟人类行为
            time.sleep(random.uniform(3, 5))

            # 6. 发布
            return self.click_publish_v2()

        except Exception as e:
            logger.error(f"❌ 发布过程出错: {e}")
            self.save_screenshot("error_publish.png")
            return False

    def upload_images_v2(self, image_paths):
        """上传图片 - 改进版"""
        logger.info(f"准备上传 {len(image_paths)} 张图片...")

        try:
            # 等待上传区域出现
            upload_area = self.page.ele(
                'css:.upload-wrapper, .upload-area, [class*="upload"]', timeout=10
            )
            if not upload_area:
                logger.warning("未找到上传区域，尝试直接找 input")

            # 找 file input（通常是隐藏的）
            file_input = self.page.ele('css:input[type="file"]', timeout=5)
            if file_input:
                # 逐个上传
                for i, img_path in enumerate(image_paths[:9]):
                    abs_path = str(Path(img_path).absolute())
                    if Path(abs_path).exists():
                        file_input.input(abs_path)
                        logger.info(f"  上传第 {i+1} 张: {Path(img_path).name}")
                        time.sleep(2)  # 等待上传进度

                # 等待所有图片上传完成
                time.sleep(3)
                logger.info("✅ 图片上传完成")
                self.save_screenshot("2_images_uploaded.png")
            else:
                logger.warning("⚠️ 未找到文件上传输入框")

        except Exception as e:
            logger.error(f"上传图片失败: {e}")

    def fill_title_v2(self, title):
        """填写标题 - 改进版"""
        logger.info(f"填写标题: {title[:20]}...")

        try:
            # 策略1：找 placeholder 包含"标题"的 input
            selectors = [
                'css:input[placeholder*="标题"]',
                'css:input[placeholder*="题目"]',
                "css:.title-input input",
                'css:input[maxlength="20"]',
                'css:[data-testid="title-input"]',
                'xpath://input[contains(@placeholder, "标题")]',
                'css:input[class*="title"]',
            ]

            for selector in selectors:
                try:
                    ele = self.page.ele(selector, timeout=3)
                    if ele:
                        ele.clear()
                        ele.input(title)
                        logger.info(f"✅ 标题填写成功 (selector: {selector})")
                        return True
                except Exception as e:
                    continue

            # 策略2：JavaScript 注入（更通用的选择器）
            js_code = f'''
                (function() {{
                    var inputs = document.querySelectorAll('input');
                    for (var i = 0; i < inputs.length; i++) {{
                        var placeholder = inputs[i].placeholder || '';
                        var maxlength = inputs[i].getAttribute('maxlength');
                        if (placeholder.indexOf('标题') !== -1 || placeholder.indexOf('题目') !== -1 || maxlength === '20') {{
                            inputs[i].value = "{title.replace('"', '\\"')}";
                            inputs[i].dispatchEvent(new Event('input', {{ bubbles: true }}));
                            inputs[i].dispatchEvent(new Event('change', {{ bubbles: true }}));
                            return 'found';
                        }}
                    }}
                    return 'not found';
                }})();
            '''
            result = self.page.run_js(js_code)
            if result == "found":
                logger.info("✅ 标题通过 JS 填写成功")
                return True

            logger.error("❌ 所有标题填写策略都失败")
            self.save_screenshot("3_title_fill_failed.png")
            return False

        except Exception as e:
            logger.error(f"填写标题失败: {e}")
            return False

    def fill_content_v2(self, content):
        """填写正文 - 改进版"""
        logger.info(f"填写正文: {len(content)} 字...")

        try:
            # 策略1：找 contenteditable 元素（富文本编辑器）
            selectors = [
                'css:.ql-editor[contenteditable="true"]',
                'css:[contenteditable="true"]',
                "css:.editor-content",
                "css:.note-textarea",
                'css:textarea[placeholder*="正文"]',
                'css:[data-testid="content-editor"]',
                'xpath://div[@contenteditable="true"]',
            ]

            for selector in selectors:
                try:
                    ele = self.page.ele(selector, timeout=3)
                    if ele:
                        ele.clear()
                        ele.input(content)
                        logger.info(f"✅ 正文填写成功 (selector: {selector})")
                        return True
                except:
                    continue

            # 策略2：JavaScript 注入
            js_code = f'''
                (function() {{
                    var editors = document.querySelectorAll('[contenteditable="true"], .ql-editor, .editor');
                    if (editors.length > 0) {{
                        editors[0].innerHTML = "{content.replace('"', '\\"').replace(chr(10), '<br>')}";
                        editors[0].dispatchEvent(new Event('input', {{ bubbles: true }}));
                        return 'found';
                    }}
                    var textareas = document.querySelectorAll('textarea');
                    for (var i = 0; i < textareas.length; i++) {{
                        if (textareas[i].placeholder.indexOf('正文') !== -1 || textareas[i].className.indexOf('content') !== -1) {{
                            textareas[i].value = "{content.replace('"', '\\"')}";
                            textareas[i].dispatchEvent(new Event('input', {{ bubbles: true }}));
                            return 'found';
                        }}
                    }}
                    return 'not found';
                }})();
            '''
            result = self.page.run_js(js_code)
            if result == "found":
                logger.info("✅ 正文通过 JS 填写成功")
                return True

            logger.error("❌ 所有正文填写策略都失败")
            self.save_screenshot("4_content_fill_failed.png")
            return False

        except Exception as e:
            logger.error(f"填写正文失败: {e}")
            return False

    def click_publish_v2(self):
        """点击发布 - 改进版"""
        logger.info("尝试点击发布...")

        try:
            # 等待一下，确保内容已填入
            time.sleep(2)

            selectors = [
                'css:button:contains("发布")',
                "css:.publish-btn",
                'css:[data-testid="publish-button"]',
                "css:.btn-publish",
                'css:button[class*="publish"]',
                'xpath://button[contains(text(), "发布")]',
            ]

            for selector in selectors:
                try:
                    btn = self.page.ele(selector, timeout=3)
                    if btn and btn.is_enabled():
                        btn.click()
                        logger.info("🚀 发布按钮已点击")

                        # 等待发布完成
                        time.sleep(5)

                        # 检查结果
                        if "note" in self.page.url or "detail" in self.page.url:
                            logger.info("✅ 发布成功！")
                            return True
                        elif "成功" in self.page.html:
                            logger.info("✅ 发布成功（检测到成功提示）")
                            return True
                        else:
                            self.save_screenshot("5_publish_result.png")
                            logger.warning("⚠️ 请手动确认发布状态")
                            return False
                except:
                    continue

            logger.error("❌ 未找到发布按钮")
            self.save_screenshot("5_publish_button_not_found.png")
            return False

        except Exception as e:
            logger.error(f"点击发布失败: {e}")
            return False

    def save_screenshot(self, filename):
        """保存截图用于调试"""
        try:
            self.page.save_screenshot(filename)
            logger.info(f"📸 截图已保存: {filename}")
        except:
            pass

    def save_cookies(self):
        """保存 Cookie"""
        try:
            cookies = self.page.cookies()
            with open(self.config["xiaohongshu_cookies"], "w", encoding="utf-8") as f:
                json.dump(cookies, f, ensure_ascii=False, indent=2)
            logger.info("💾 Cookie 已保存")
        except Exception as e:
            logger.error(f"保存 Cookie 失败: {e}")

    def run_single(self, topic, images=None):
        """发布单篇笔记"""
        logger.info(f"\n{'='*60}")
        logger.info(f"开始发布: {topic}")
        logger.info(f"{'='*60}")

        # 初始化
        if not self.init_browser():
            return False

        try:
            # 登录
            if not self.login():
                return False

            # 生成内容
            title, content = self.generate_content(topic)
            if not title or not content:
                logger.error("内容生成失败，跳过")
                return False

            # 准备图片
            image_paths = []
            if images:
                for img in images:
                    if Path(img).exists():
                        image_paths.append(img)

            # 发布
            result = self.publish_note(title, content, image_paths)

            # 保存 Cookie
            self.save_cookies()

            return result

        except Exception as e:
            logger.error(f"运行出错: {e}", exc_info=True)
            return False
        finally:
            if self.page:
                self.page.quit()
                logger.info("浏览器已关闭")

    def run_batch(self):
        """批量发布（从文件读取主题）"""
        topics_file = self.config.get("topics_file", "./topics.txt")

        if not Path(topics_file).exists():
            logger.error(f"主题文件不存在: {topics_file}")
            return

        with open(topics_file, "r", encoding="utf-8") as f:
            topics = [
                line.strip() for line in f if line.strip() and not line.startswith("#")
            ]

        logger.info(
            f"共读取 {len(topics)} 个主题，每日限制 {self.config['daily_limit']} 篇"
        )

        published = 0
        for i, topic in enumerate(topics):
            if published >= self.config["daily_limit"]:
                logger.info(f"已达到每日限制 {self.config['daily_limit']} 篇，停止发布")
                break

            success = self.run_single(topic)

            if success:
                published += 1
                logger.info(f"已成功发布 {published}/{self.config['daily_limit']} 篇")

            # 间隔时间
            if i < len(topics) - 1:
                delay = random.randint(
                    self.config["publish_interval"]["min"],
                    self.config["publish_interval"]["max"],
                )
                logger.info(f"⏳ 等待 {delay} 秒后继续...")
                time.sleep(delay)

        logger.info(f"批量发布完成，共发布 {published} 篇")


# ==================== 使用方式 ====================


def main():
    import sys

    # 创建示例配置文件
    config_example = {
        "openclaw_url": "http://localhost:18789",
        "openclaw_token": None,
        "headless": True,
        "daily_limit": 2,
        "publish_interval": {"min": 600, "max": 1200},  # 10-20分钟
    }

    if not Path("config.json").exists():
        with open("config.json", "w", encoding="utf-8") as f:
            json.dump(config_example, f, indent=2, ensure_ascii=False)
        print("已创建 config.json 模板，请编辑配置")
        return

    # 创建示例主题文件
    if not Path("topics.txt").exists():
        with open("topics.txt", "w", encoding="utf-8") as f:
            f.write("# 每行一个主题，#开头为注释\n")
            f.write("大理古城旅行攻略\n")
            f.write("上海探店｜隐藏咖啡馆\n")
            f.write("OOTD｜春日穿搭分享\n")
        print("已创建 topics.txt 模板")
        return

    publisher = XHSAutoPublisherServer("config.json")

    if len(sys.argv) > 1:
        # 命令行参数：单篇发布
        topic = sys.argv[1]
        images = sys.argv[2:] if len(sys.argv) > 2 else None
        publisher.run_single(topic, images)
    else:
        # 批量发布
        publisher.run_batch()


if __name__ == "__main__":
    main()
