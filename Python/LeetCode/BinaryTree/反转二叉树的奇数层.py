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
    def reverseOddLevels(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return

        def dfs(root1: Optional[TreeNode], root2: Optional[TreeNode], dp: int):
            if not root1 or not root2:
                return
            if dp & 1:
                root1.val, root2.val = root2.val, root1.val
            dfs(root1.left, root2.right, dp + 1)
            dfs(root1.right, root2.left, dp + 1)

        dfs(root.left, root.right, 1)

        return root
