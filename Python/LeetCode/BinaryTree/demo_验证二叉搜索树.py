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


# 后序遍历
class Solution1:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:

        def dfs(root: Optional[TreeNode]):
            if root is None:
                return inf, -inf, True
            leftmin, leftmax, lj = dfs(root.left)
            rightmin, rightmax, rj = dfs(root.right)
            if not lj or not rj:
                return root.val, root.val, False
            if not leftmax < root.val < rightmin:
                return root.val, root.val, False

            return (
                min(root.val, leftmin, rightmin),
                max(root.val, leftmax, rightmax),
                True,
            )

        return dfs(root)[2]


# 中序遍历
class Solution2:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        pre = -inf

        def dfs(root: Optional[TreeNode]) -> bool:
            if not root:
                return True
            if not dfs(root.left):
                return False
            nonlocal pre
            if pre >= root.val:
                return False
            pre = root.val
            return dfs(root.right)

        return dfs(root)


# 前序遍历
class Solution:
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(root: Optional[TreeNode], low: int, high: int) -> bool:
            if root is None:
                return True
            if not (low < root.val < high):
                return False
            return dfs(root.left, low, root.val) and dfs(root.right, root.val, high)

        return dfs(root, -inf, inf)


if __name__ == "__main__":
    root = TreeNode(2)
    root.left = TreeNode(1)
    root.right = TreeNode(3)
    print(Solution().isValidBST(root))
