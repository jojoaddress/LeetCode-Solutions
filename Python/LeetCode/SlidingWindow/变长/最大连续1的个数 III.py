from typing import List
from collections import defaultdict


class Solution:
    def longestOnes(self, nums: List[int], k: int) -> int:
        cnt = defaultdict(int)
        maxLen = 0
        left = 0
        for i, num in enumerate(nums):
            cnt[num] += 1
            while cnt[0] > k:
                cnt[nums[left]] -= 1
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen


if __name__ == "__main__":
    print(Solution().longestOnes([1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0], 2))
