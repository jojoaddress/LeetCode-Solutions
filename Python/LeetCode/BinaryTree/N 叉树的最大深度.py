from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children

class Solution:
    def maxDepth(self, root: 'Node') -> int:
        if not root:
            return 0
        maxd = 1
        def dfs(root:'Node',d:int)->None:
            if not root:
                return
            for c in root.children:
                dfs(c,d+1)
            nonlocal maxd
            maxd = max(d,maxd)
        dfs(root,1)
        return maxd
    
class Solution:
    def maxDepth(self, root: 'Node') -> int:
        if not root:
            return 0
        return max((self.maxDepth(c) for c in root.children),default=0)+1