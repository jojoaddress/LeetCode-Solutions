from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque

class Solution:
    def minReorder(self, n: int, connections: List[List[int]]) -> int:
        g = [[] for _ in range(n)]
        for x,y in connections:
            g[x].append([y,1])
            g[y].append([x,0])
        def dfs(x:int,fa:int):
            res = 0
            for y in g[x]:
                if y[0] != fa:
                    res += y[1] + dfs(y[0],x)
            return res
        return dfs(0,-1)