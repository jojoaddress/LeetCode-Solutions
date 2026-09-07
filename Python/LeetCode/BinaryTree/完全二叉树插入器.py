from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class CBTInserter:

    def __init__(self, root: Optional[TreeNode]):
        self.root = root
        self.candidate = deque()
        q = deque([root])
        while q:
            node = q.popleft()
            if node.left:
                q.append(node.left)
            if node.right:
                q.append(node.right)
            if not (node.left and node.right):
                self.candidate.append(node)

    def insert(self, val: int) -> int:
        candidate = self.candidate
        child = TreeNode(val)
        fa = candidate[0]
        if not fa.left:
            fa.left = child
        else:
            fa.right = child
            candidate.popleft()
        candidate.append(child)
        return fa.val

    def get_root(self) -> Optional[TreeNode]:
        return self.root
