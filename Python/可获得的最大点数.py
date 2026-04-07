from typing import List
from collections import defaultdict


# cardPoints = [1,2,3,4,5,6,1]
#               0 1 2 3 4 5 6
class Solution:
    def maxScore(self, cardPoints: List[int], k: int) -> int:
        n = len(cardPoints)
        l1 = cardPoints[:k]
        l2 = cardPoints[n - k :]
        s = l2 + l1
        res = 0
        temp = 0
        for i, c in enumerate(s):
            temp += c
            left = i - k + 1
            if left < 0:
                continue
            res = max(temp, res)
            temp -= s[left]
        return res


if __name__ == "__main__":
    cardPoints = [1, 2, 3, 4, 5, 6, 1]
    k = 3
    print(Solution().maxScore(cardPoints, k))
