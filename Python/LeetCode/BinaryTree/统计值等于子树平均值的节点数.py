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
    def averageOfSubtree(self, root: TreeNode) -> int:

        res = 0

        def dfs(root: Optional[TreeNode]) -> tuple[int, int]:
            nonlocal res
            if not root:
                return (0, 0)
            left, lefti = dfs(root.left)
            right, righti = dfs(root.right)
            if (root.val + left + right) // (lefti + righti + 1) == root.val:
                res += 1
            return (root.val + left + right, lefti + righti + 1)

        dfs(root)
        return res


if __name__ == "__main__":
    root = TreeNode(4)
    root.left = TreeNode(8)
    root.right = TreeNode(5)
    root.left.left = TreeNode(0)
    root.left.right = TreeNode(1)
    root.right.right = TreeNode(6)
    print(Solution().averageOfSubtree(root))
