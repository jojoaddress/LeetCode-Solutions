from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children

class Solution:
    def postorder(self, root: 'Node') -> List[int]:
        res = []
        def dfs(root:'Node')->None:
            if not root:
                return
            for c in root.children:
                dfs(c)
            res.append(root.val)

        dfs(root)
        return res  