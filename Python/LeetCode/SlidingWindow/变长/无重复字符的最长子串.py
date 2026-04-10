from typing import List
from collections import defaultdict


class Solution:
    def lengthOfLongestSubstring(self, s: str) -> int:
        cnt = defaultdict(int)
        maxLen = 0
        left = 0
        for i, c in enumerate(s):
            cnt[c] += 1
            while cnt[c] > 1:
                cnt[s[left]] -= 1
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen


if __name__ == "__main__":
    print(Solution().lengthOfLongestSubstring("abcabcbb"))
