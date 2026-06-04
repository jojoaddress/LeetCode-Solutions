from typing import List
from typing import Optional
from collections import defaultdict
from math import inf
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def deepestLeavesSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        q = deque([root])
        res = 0
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            res = sum(vis)
        return res
