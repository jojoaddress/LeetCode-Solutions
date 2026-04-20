from typing import List
from typing import Optional
from collections import defaultdict


class Solution:
    def findDuplicate(self, nums: List[int]) -> int:
        left = right = 0
        while True:
            left = nums[left]
            right = nums[nums[right]]
            if left == right:
                break
        head = 0
        while head != left:
            head = nums[head]
            left = nums[left]
        return head


if __name__ == "__main__":
    nums = [1, 3, 4, 2, 2]
    print(Solution().findDuplicate(nums))
