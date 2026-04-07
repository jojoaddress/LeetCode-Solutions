from typing import List
from collections import Counter


class Solution:
    def maxSum(self, nums: List[int], m: int, k: int) -> int:
        res = 0
        temp = 0
        vist = Counter()
        distinct = 0
        for i, num in enumerate(nums):
            temp += num
            left = i - k + 1
            if vist[num] == 0:
                distinct += 1
            vist[num] += 1
            if left < 0:
                continue
            if m <= distinct:
                res = max(res, temp)
            leftVal = nums[left]
            vist[leftVal] -= 1
            if vist[leftVal] == 0:
                distinct -= 1
            temp -= nums[left]
        return res


if __name__ == "__main__":
    nums = [1, 1, 1, 3]
    m = 2
    k = 2
    print(Solution().maxSum(nums, m, k))
