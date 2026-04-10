from typing import List


class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        res = temp = 0
        for i, c in enumerate(s):
            # 第一步：入      
            if s[i] in "aeiou":
                temp += 1
            left = i - k + 1
            if left < 0:
                continue
            # 第二步：更新
            res = max(res, temp)
            # 第三步：出
            if s[left] in "aeiou":
                temp -= 1
        return res

if __name__ == "__main__":
    print(Solution().maxVowels("abciiidef", 3))