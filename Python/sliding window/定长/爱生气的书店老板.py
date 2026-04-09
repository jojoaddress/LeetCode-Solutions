from typing import List
from collections import defaultdict


class Solution:
    def maxSatisfied(
        self, customers: List[int], grumpy: List[int], minutes: int
    ) -> int:
        maxSum = 0
        sum1 = 0
        sum2 = 0
        for i, customer in enumerate(customers):
            jud = grumpy[i]
            if jud == 0:
                sum1 += customer
            else:
                sum2 += customer
            left = i - minutes + 1
            maxSum = max(maxSum, sum2)
            if left < 0:
                continue
            if grumpy[left]:
                sum2 -= customers[left]
        return sum1 + maxSum


if __name__ == "__main__":
    customers = [2, 4, 1, 4, 1]
    grumpy = [1, 0, 1, 0, 1]
    minutes = 2
    print(Solution().maxSatisfied(customers, grumpy, minutes))
