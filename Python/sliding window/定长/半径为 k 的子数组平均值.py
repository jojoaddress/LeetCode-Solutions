from typing import List


class Solution:
    def getAverages(self, nums: List[int], k: int) -> List[int]:
        res = [-1] * len(nums)
        temp = 0
        k2 = 2 * k + 1
        for i, num in enumerate(nums):
            temp += num
            left = i - k2 + 1
            if left < 0:
                continue
            res[i - k] = int(temp / k2)
            temp -= nums[left]
        return res


if __name__ == "__main__":
    nums = [7, 4, 3, 9, 1, 8, 5, 2, 6]
    k = 3
    print(Solution().getAverages(nums, k))
