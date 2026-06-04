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
    def replaceValueInTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return
        root.val = 0
        q = deque([root])
        while q:
            tmp = q
            q = []
            sumlevel = 0
            for node in tmp:
                if node.left:
                    q.append(node.left)
                    sumlevel += node.left.val
                if node.right:
                    q.append(node.right)
                    sumlevel += node.right.val
            for node in tmp:
                sumChild = (node.left.val if node.left else 0) + (
                    node.right.val if node.right else 0
                )
                if node.left:
                    node.left.val = sumlevel - sumChild
                if node.right:
                    node.right.val = sumlevel - sumChild
        return root
