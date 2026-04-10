from typing import List
from collections import defaultdict

class Solution:
    def maximumUniqueSubarray(self, nums: List[int]) -> int:
        maxCost = 0
        currentCost = 0
        left = 0
        cnt = defaultdict(int)
        for i,num in enumerate(nums):
            cnt[num] += 1
            currentCost += num
            while cnt[num] > 1:
                cnt[nums[left]] -= 1
                currentCost -= nums[left]
                left += 1
            maxCost = max(maxCost,currentCost)
        return maxCost

if __name__ == "__main__":
    print(Solution().maximumUniqueSubarray([5,2,1,2,5,2,1,2,5]))