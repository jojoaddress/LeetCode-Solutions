# 创建 convert_cookie.py 文件
import json

# 把你从浏览器复制的 JSON 粘贴到这里（注意是数组格式）
browser_cookies = """
[
  {
    "name": "a1",
    "value": "19cd6fd8c83zu3osysuk4dzx7qtuz4xpyjgvaml9r50000202635",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1809582266,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "abRequestId",
    "value": "751e17a8-0360-562a-b639-6aa11449443f",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1809582265,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "acw_tc",
    "value": "0a00d5b517731334654181131e6b81cbfb12e7a83250472646bbf9ef73d6da",
    "domain": "www.xiaohongshu.com",
    "path": "/",
    "expires": 1773134065,
    "httpOnly": true,
    "secure": false
  },
  {
    "name": "gid",
    "value": "yjSfKifjDDv2yjSfKifYSV61Yqu7qlMvM7T4kjFfuCWA9h287u4CU0888J8JKq28WdYKJWfy",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1813093592,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "id_token",
    "value": "VjEAAL2+PEHZLedtc2vKms8rZCSVKn/2h2ZXKgbclnc/qSYLPBix6Mz+w7m8M+7IwEGMPnMyk+AoaRQ9JRY4zpxowLYusQJR+oX//GADJfzsEn8QxuPdb1oxXbWLkZQuOvzynBFA",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1809582287,
    "httpOnly": true,
    "secure": true
  },
  {
    "name": "loadts",
    "value": "1773133466746",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1809582266,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "sec_poison_id",
    "value": "977e09be-7f76-4e10-b1c1-c4ae69756deb",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1773132872,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "unread",
    "value": "{%22ub%22:%226466b80b0000000014024674%22%2C%22ue%22:%22648545130000000013014a0c%22%2C%22uc%22:19}",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": -1,
    "httpOnly": false,
    "secure": false
  },
  {
    "name": "web_session",
    "value": "040069b8236da0352ba6c6969a3b4bfbc66b75",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": 1809582287,
    "httpOnly": true,
    "secure": true
  },
  {
    "name": "webBuild",
    "value": "5.14.2",
    "domain": ".xiaohongshu.com",
    "path": "/",
    "expires": -1,
    "httpOnly": false,
    "secure": false
  }
]
"""

# 转换为 DrissionPage 格式
cookies_list = json.loads(browser_cookies)
formatted_cookies = []

for cookie in cookies_list:
    formatted_cookies.append(
        {
            "name": cookie["name"],
            "value": cookie["value"],
            "domain": cookie.get("domain", ".xiaohongshu.com"),
            "path": cookie.get("path", "/"),
            "expires": cookie.get("expires", -1),
            "httpOnly": cookie.get("httpOnly", False),
            "secure": cookie.get("secure", True),
            "sameSite": cookie.get("sameSite", "Lax"),
        }
    )

# 保存
with open("xhs_cookies.json", "w", encoding="utf-8") as f:
    json.dump(formatted_cookies, f, ensure_ascii=False, indent=2)

print("✅ Cookie 已转换并保存到 xhs_cookies.json")
print(f"共 {len(formatted_cookies)} 个 Cookie")
