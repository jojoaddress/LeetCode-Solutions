from typing import List
from typing import Optional
from collections import defaultdict
from math import inf


class Solution:
    def countGoodNodes(self, edges: List[List[int]]) -> int:
        g = [[] for _ in range(len(edges) + 1)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        ans = 0

        def dfs(x: int, fa: int):
            size, sz0, jud = 1, 0, True
            for c in g[x]:
                if fa == c:
                    continue
                sz = dfs(c, x)
                if sz0 == 0:
                    sz0 = sz
                if sz != sz0:
                    jud = False
                size += sz
            nonlocal ans
            ans += jud
            return size
        dfs(0,-1)
        return ans
