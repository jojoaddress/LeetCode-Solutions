# 本地临时脚本 get_cookie.py
from DrissionPage import ChromiumPage
import json
import time

page = ChromiumPage()
page.get("https://www.xiaohongshu.com")

print("请扫码登录...")
time.sleep(60)  # 等待登录

# 保存 Cookie
cookies = page.cookies()
with open("xhs_cookies.json", "w", encoding="utf-8") as f:
    json.dump(cookies, f, ensure_ascii=False, indent=2)
print("Cookie 已保存到 xhs_cookies.json")
page.quit()
