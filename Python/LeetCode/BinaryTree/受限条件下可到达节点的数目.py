from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque

class Solution:
    def reachableNodes(self, n: int, edges: List[List[int]], restricted: List[int]) -> int:
        r = set(restricted)
        g = [[] for _ in range(n)]
        for x,y in edges:
            if x not in r and y not in r:
                g[x].append(y)
                g[y].append(x)
        
        def dfs(x:int,fa:int):
            cnt = 1
            for y in g[x]:
                if y != fa:
                    cnt += dfs(y,x)
            return cnt
        return dfs(0,-1)