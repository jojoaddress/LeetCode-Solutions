from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class Node:
    def __init__(self, val: Optional[int] = None, children: Optional[List['Node']] = None):
        self.val = val
        self.children = children

class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        if not root:
            return []
        q = deque([root])
        res = []
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                q.extend(node.children)
            res.append(vis)
        return res
    
class Solution:
    def levelOrder(self, root: 'Node') -> List[List[int]]:
        if not root:
            return []
        q = [root]
        res = []
        while q:
            res.append([node.val for node in q])
            q = [c for node in q for c in node.children]
        return res