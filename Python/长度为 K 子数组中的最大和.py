from typing import List
from collections import defaultdict


class Solution:
    def maximumSubarraySum(self, nums: List[int], k: int) -> int:
        res = 0
        dic = defaultdict(int)
        temp = 0
        for i, num in enumerate(nums):
            temp += num
            dic[num] += 1
            left = i - k + 1
            if left < 0:
                continue
            if len(dic) == k:
                res = max(res, temp)
            leftVal = nums[left]
            dic[leftVal] -= 1
            if dic[leftVal] == 0:
                del dic[leftVal]
            temp -= leftVal
        return res


if __name__ == "__main__":
    nums = [1, 5, 4, 2, 9, 9, 9]
    k = 3
    print(Solution().maximumSubarraySum(nums, k))
