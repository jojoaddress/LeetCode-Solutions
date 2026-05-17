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


# 后续遍历，有些丑陋
class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        res = inf

        def dfs(root: Optional[TreeNode]) -> tuple[int, int]:
            if root is None:
                return inf, -inf
            if not root.left and not root.right:
                return root.val, root.val
            leftmin, leftmax = dfs(root.left)
            rightmin, rightmax = dfs(root.right)
            nonlocal res
            tmp1 = abs(root.val - leftmax)
            tmp2 = abs(rightmin - root.val)
            res = min(res, tmp1, tmp2)
            return min(leftmin, rightmin, root.val), max(leftmax, rightmax, root.val)

        dfs(root)
        return res


# 中序遍历
class Solution:
    def getMinimumDifference(self, root: Optional[TreeNode]) -> int:
        pre = -inf
        res = inf

        def dfs(root: Optional[TreeNode]):
            if root is None:
                return
            dfs(root.left)
            nonlocal res, pre
            res = min(res, abs(root.val - pre))
            pre = root.val
            dfs(root.right)

        dfs(root)
        return res
