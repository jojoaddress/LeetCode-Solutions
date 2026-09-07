from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from collections import deque
from math import inf


class Solution:
    def baseUnitConversions(self, conversions: List[List[int]]) -> List[int]:
        mod = 1000000007
        n = len(conversions)
        g = [[] for _ in range(n + 1)]
        info = [1] * (n + 1)
        for con in conversions:
            g[con[0]].append(con[1])
            info[con[1]] = con[2]
        res = [0] * (n + 1)

        def dfs(x: int, pathsum: int):
            res[x] = (pathsum * info[x]) % mod
            for c in g[x]:
                dfs(c, res[x])

        dfs(0, 1)
        return res


if __name__ == "__main__":
    conversions = [
        [0, 1, 2],
        [0, 2, 3],
        [1, 3, 4],
        [1, 4, 5],
        [2, 5, 2],
        [4, 6, 3],
        [5, 7, 4],
    ]
    print(Solution().baseUnitConversions(conversions))
