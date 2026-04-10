from typing import List
from collections import defaultdict


class Solution:
    def minArrivalsToDiscard(self, arrivals: List[int], w: int, m: int) -> int:
        cnt = defaultdict(int)
        res = 0
        for i, x in enumerate(arrivals):
            if cnt[x] == m:
                arrivals[i] = 0
                res += 1
            else:
                cnt[x] += 1
            left = i - w + 1
            if left >= 0:
                cnt[arrivals[left]] -= 1

        return res


if __name__ == "__main__":
    print(Solution().minArrivalsToDiscard([1, 2, 1, 3, 1], 4, 2))
