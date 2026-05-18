from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate
from math import inf

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def lcaDeepestLeaves(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        def dfs(root: Optional[TreeNode]) -> tuple[Optional[TreeNode], int]:
            if not root:
                return None, 0
            leftNode, leftDepth = dfs(root.left)
            rightNode, rightDepth = dfs(root.right)

            if leftDepth > rightDepth:
                return leftNode, leftDepth + 1
            if leftDepth < rightDepth:
                return rightNode, rightDepth + 1
            return root, leftDepth + 1

        return dfs(root)[0]