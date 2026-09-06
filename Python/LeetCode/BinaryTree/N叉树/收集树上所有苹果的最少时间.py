from typing import List
from typing import Optional
from collections import defaultdict
from math import inf

class Solution:
    def minTime(self, n: int, edges: List[List[int]], hasApple: List[bool]) -> int:
        g = [[] for _ in range(n)]
        for u,v in edges:
            g[u].append(v)
            g[v].append(u)

        
        def dfs(x:int,fa:int):
            for c in g[x]:
                if c == fa:
                    continue
                dfs(c,x)
                if hasApple[c]:
                    hasApple[x]=True
        
        dfs(0,-1)
        res = 0
        for u,v in edges:
            if hasApple[u] and hasApple[v]:
                res+=1
        return res*2
    
if __name__ == "__main__":
    s = Solution()
    print(s.minTime(7, [[0,1],[0,2],[1,4],[1,5],[2,3],[2,6]], [False,False,True,False,True,True,False]))
