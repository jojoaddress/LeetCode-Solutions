from typing import List
from collections import defaultdict


class Solution:
    def longestSemiRepetitiveSubstring(self, s: str) -> int:
        same = 0
        maxLen = 1
        left = 0
        for i in range(1, len(s)):
            same += s[i] == s[i - 1]
            if same > 1:
                left += 1
                while s[left] != s[left - 1]:
                    left += 1
                same -= 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen
    
if __name__ == "__main__":
    print(Solution().longestSemiRepetitiveSubstring("1111111"))
