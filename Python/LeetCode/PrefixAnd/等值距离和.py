from typing import List
from typing import Optional
from itertools import accumulate
from collections import defaultdict


class Solution:
    def distance(self, nums: List[int]) -> List[int]:
        groups = defaultdict(list)
        for i, x in enumerate(nums):
            groups[x].append(i)
        ans = [0] * len(nums)

        for a in groups.values():
            sum = list(accumulate(a, initial=0))
            n = len(a)
            for j, target in enumerate(a):
                left = j * target - sum[j]
                right = sum[n] - sum[j] - (n - j) * target
                ans[target] = left + right
        return ans
