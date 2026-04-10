from typing import List
from collections import defaultdict


class Solution:
    def maximumLengthSubstring(self, s: str) -> int:
        maxLen = 0
        left = 0
        cnt = defaultdict(int)
        for i, c in enumerate(s):
            cnt[c] += 1
            while cnt[c] > 2:
                cnt[s[left]] -= 1
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen


if __name__ == "__main__":
    print(Solution().maximumLengthSubstring("bcbbbcba"))
