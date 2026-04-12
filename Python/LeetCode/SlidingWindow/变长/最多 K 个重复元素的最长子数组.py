from typing import List
from collections import defaultdict

class Solution:
    def maxSubarrayLength(self, nums: List[int], k: int) -> int:
        maxLen = 0
        left = 0
        cnt = defaultdict(int)
        for i,num in enumerate(nums):
            cnt[num] += 1
            while cnt[num] > k:
                cnt[nums[left]] -= 1
                left += 1
            maxLen = max(maxLen,i-left+1)
        return maxLen

if __name__ == "__main__":
    print(Solution().maxSubarrayLength([1,2,3,1,2,3,1,2],2))