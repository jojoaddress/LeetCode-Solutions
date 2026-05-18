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
    def rangeSumBST(self, root: Optional[TreeNode], low: int, high: int) -> int:
        res = 0

        def dfs(root: Optional[TreeNode]) -> None:
            if root is None:
                return
            dfs(root.left)
            nonlocal res
            if low <= root.val <= high:
                res += root.val
            dfs(root.right)

        dfs(root)
        return res
