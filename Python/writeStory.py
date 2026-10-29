import os
import time
import random
import threading
from pynput import keyboard
from pynput.keyboard import Key, Controller

kb = Controller()

# ==================== 1. 路径与基础配置 ====================

DEFAULT_FILE_PATH = r"d:\Desktop\个人\小说\test.txt"

# 拟真错字控制
ENABLE_TYPOS = True             # 是否开启“打错字并退格重输”
TYPO_PROBABILITY = 0.02         # 错字概率（2%）

# 换行模式配置（普通写作软件保持 False）
USE_SHIFT_ENTER_FOR_NEWLINE = False

# 软件自动补全的后置符号：遇到时直接按右箭头滑过，避免多余符号
AUTO_SKIP_CLOSING_CHARS = {"”", "】"}

# ==================== 2. 三档位调速配置表 ====================

SPEED_PROFILES = {
    1: {
        "name": "低档 (约 5,000 字/小时)",
        "char_delay": (0.35, 0.60),     # 基础敲击延迟
        "short_punc": (0.6, 1.2),       # 逗号、顿号、分号停顿
        "long_punc": (1.8, 3.5),        # 句号、问号、换行停顿
        "think_prob": 0.025,            # 构思停顿概率
        "think_delay": (2.5, 5.0)       # 构思停顿秒数
    },
    2: {
        "name": "中档 (约 8,000 字/小时)",
        "char_delay": (0.20, 0.38),
        "short_punc": (0.35, 0.70),
        "long_punc": (1.0, 2.0),
        "think_prob": 0.015,
        "think_delay": (1.5, 3.0)
    },
    3: {
        "name": "高档 (约 10,000 字/小时)",
        "char_delay": (0.14, 0.28),
        "short_punc": (0.25, 0.50),
        "long_punc": (0.6, 1.4),
        "think_prob": 0.01,
        "think_delay": (1.0, 2.0)
    }
}

# 当前档位（默认 1 档：低档）
current_gear = 1

# ==================== 3. 全局状态与断点续打 ====================
is_running = False          # 当前打字状态
loaded_text = ""            # 全部待打文本
current_index = 0           # 断点续打字符指针

TYPO_CANDIDATES = "abcdefghijklmnopqrstuvwxyz1234567890"

def load_text_from_file(file_path: str) -> str:
    """读取指定路径的文本文件"""
    clean_path = file_path.strip().strip("'").strip('"')
    if not os.path.exists(clean_path):
        raise FileNotFoundError(f"找不到指定的文件: {clean_path}")
    
    with open(clean_path, "r", encoding="utf-8") as f:
        return f.read()

def simulate_typo_and_correct(correct_char: str):
    """模拟打错字 -> 反应迟钝停顿 -> 退格删除 -> 补打正确字"""
    wrong_char = random.choice(TYPO_CANDIDATES)
    kb.type(wrong_char)
    
    time.sleep(random.uniform(0.20, 0.35))
    kb.tap(Key.backspace)
    time.sleep(random.uniform(0.12, 0.25))
    kb.type(correct_char)

def interruptible_sleep(seconds: float):
    """支持毫秒级响应暂停的等待逻辑（修复负数报错 & 使用高精单调时钟）"""
    end_time = time.perf_counter() + seconds
    while is_running:
        remaining = end_time - time.perf_counter()
        # 1. 剩余等待时间归零或变为负数，直接跳出循环
        if remaining <= 0:
            break
        # 2. 限制单次等待步长，保证数值严格为正数
        sleep_step = min(0.04, remaining)
        if sleep_step > 0:
            time.sleep(sleep_step)

def human_like_typing():
    """断点续打工作线程（动态读取当前档位速度）"""
    global is_running, current_index

    time.sleep(0.5)

    short_punctuations = set("，、；,;")
    long_punctuations = set("。！？.!?\n")
    total_len = len(loaded_text)

    while current_index < total_len:
        if not is_running:
            print(f"\n[已暂停] 当前停在第 {current_index}/{total_len} 字。按 F8 即可继续。")
            return

        char = loaded_text[current_index]

        # 1. 换行符处理
        if char == '\n':
            if USE_SHIFT_ENTER_FOR_NEWLINE:
                with kb.pressed(Key.shift):
                    kb.tap(Key.enter)
            else:
                kb.tap(Key.enter)

        # 2. 软件自动补全的后置符号：按右箭头滑过
        elif char in AUTO_SKIP_CLOSING_CHARS:
            kb.tap(Key.right)

        # 3. 文本输入与拟真错字
        else:
            if ENABLE_TYPOS and char.isalnum() and random.random() < TYPO_PROBABILITY:
                simulate_typo_and_correct(char)
            else:
                kb.type(char)

        current_index += 1

        # 4. 动态读取当前档位的延迟参数
        profile = SPEED_PROFILES[current_gear]
        base_delay = random.uniform(*profile["char_delay"])

        if char in short_punctuations:
            base_delay += random.uniform(*profile["short_punc"])
        elif char in long_punctuations:
            base_delay += random.uniform(*profile["long_punc"])
        elif random.random() < profile["think_prob"]:
            base_delay += random.uniform(*profile["think_delay"])

        interruptible_sleep(base_delay)

    is_running = False
    print(f"\n[完成] 全部文本已成功输入完毕！(共 {total_len} 字)")

# ==================== 4. 热键与调度控制 ====================

def switch_gear():
    """切换档位：低档(1) -> 中档(2) -> 高档(3) -> 低档(1)"""
    global current_gear
    current_gear = 1 if current_gear >= 3 else current_gear + 1
    print(f"\n⚡ [档位切换] >>> 当前速度：{SPEED_PROFILES[current_gear]['name']}")

def toggle_start_pause():
    global is_running, current_index
    if not loaded_text:
        print("\n[警告] 未读取到文本内容！")
        return

    if is_running:
        is_running = False
    else:
        if current_index >= len(loaded_text):
            print("\n[提示] 文本已打完。按 [F9] 可重置进度。")
            return
        
        is_running = True
        status = "开始" if current_index == 0 else f"继续（第 {current_index + 1} 字）"
        print(f"\n[状态] {status}打字中（当前档位：{SPEED_PROFILES[current_gear]['name']}）... 按 F8 暂停，F7 调速。")
        threading.Thread(target=human_like_typing, daemon=True).start()

def reset_progress():
    global is_running, current_index
    if is_running:
        is_running = False
        time.sleep(0.1)
    current_index = 0
    print(f"\n[重置] 进度已归零，下次按 F8 将从头开始！")

def on_press(key):
    if key == Key.f7:
        switch_gear()
    elif key == Key.f8:
        toggle_start_pause()
    elif key == Key.f9:
        reset_progress()
    elif key == Key.esc:
        print("\n[退出] 程序已终止。")
        os._exit(0)

if __name__ == "__main__":
    print("=" * 65)
    print("【拟人化自动打字脚本 - 三档位调速版】")
    print("=" * 65)

    target_path = DEFAULT_FILE_PATH
    if not os.path.exists(target_path):
        while True:
            user_input = input("未找到默认文件，请拖入 txt 文件后回车: ").strip()
            user_input = user_input.strip("'").strip('"')
            if os.path.exists(user_input):
                target_path = user_input
                break
            else:
                print("❌ 文件路径不存在，请重新输入！")

    try:
        loaded_text = load_text_from_file(target_path)
        print(f"✔ 文本加载成功: {target_path}")
        print(f"✔ 待输入字数: {len(loaded_text)} 字")
        print(f"✔ 初始档位: {SPEED_PROFILES[current_gear]['name']}")
    except Exception as e:
        print(f"❌ 读取文件失败: {e}")
        exit(1)

    print("\n" + "-" * 65)
    print("【快捷键控制】")
    print("  [F7]  切换速度档位（低档 5k -> 中档 8k -> 高档 10k，随时可切）")
    print("  [F8]  开始 / 暂停 / 接着打（一键切换）")
    print("  [F9]  重置进度（从第 1 个字重新开始）")
    print("  [Esc] 彻底退出脚本")
    print("-" * 65)

    with keyboard.Listener(on_press=on_press) as listener:
        listener.join()