from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from collections import deque
from math import inf


# 自顶向下
class Solution1:
    def numOfMinutes(
        self, n: int, headID: int, manager: List[int], informTime: List[int]
    ) -> int:
        g = [[] for _ in range(n)]
        for i, fa in enumerate(manager):
            if fa != -1:
                g[fa].append(i)
        res = 0

        def dfs(x: int, pathsum: int):
            pathsum += informTime[x]
            nonlocal res
            res = max(res, pathsum)
            for c in g[x]:
                dfs(c, pathsum)

        dfs(headID, 0)
        return res


# 自底向上
class Solution:
    def numOfMinutes(
        self, n: int, headID: int, manager: List[int], informTime: List[int]
    ) -> int:
        g = [[] for _ in range(n)]
        for i, fa in enumerate(manager):
            if fa != -1:
                g[fa].append(i)

        def dfs(x: int) -> int:
            res = 0
            for c in g[x]:
                res = max(res, dfs(c))
            return res + informTime[x]

        return dfs(headID)


if __name__ == "__main__":
    n = 6
    headID = 2
    manager = [2, 2, -1, 2, 2, 2]
    informTime = [0, 0, 1, 0, 0, 0]
    print(Solution().numOfMinutes(n, headID, manager, informTime))
