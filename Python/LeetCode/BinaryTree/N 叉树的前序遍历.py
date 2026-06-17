from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children

class Solution:
    def preorder(self, root: 'Node') -> List[int]:
        res = []
        def dfs(root:'Node'):
            if not root:
                return
            res.append(root.val)
            for c in root.children:
                dfs(c)
        dfs(root)
        return res