from typing import List
from collections import defaultdict


class Solution:
    def longestSubarray(self, nums: List[int]) -> int:
        left = 0
        maxLen = 0
        cnt = defaultdict(int)
        for i, num in enumerate(nums):
            cnt[num] += 1
            while cnt[0] > 1:
                cnt[nums[left]] -= 1
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen - 1


if __name__ == "__main__":
    print(Solution().longestSubarray([0, 1, 1, 1, 0, 1, 1, 0, 1]))
