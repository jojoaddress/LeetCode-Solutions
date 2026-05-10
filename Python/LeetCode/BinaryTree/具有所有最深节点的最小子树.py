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


# 自底向上
class Solution1:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
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


# 自上向下
class Solution:
    def subtreeWithAllDeepest(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        res = None
        max_depth = 0

        def dfs(root: Optional[TreeNode], depth: int) -> int:
            nonlocal res, max_depth
            if not root:
                max_depth = max(depth, max_depth)
                return depth
            left_max = dfs(root.left, depth + 1)
            right_max = dfs(root.right, depth + 1)
            if left_max == right_max == max_depth:
                res = root
            return max(left_max, right_max)

        dfs(root, 0)
        return res


if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(3)
    root.left = TreeNode(5)
    root.right = TreeNode(1)
    root.left.left = TreeNode(6)
    root.left.right = TreeNode(2)
    root.right.left = TreeNode(0)
    root.right.right = TreeNode(8)
    root.left.right.left = TreeNode(7)
    root.left.right.right = TreeNode(4)

    print(solution.subtreeWithAllDeepest(root).val)  # Output: 2
