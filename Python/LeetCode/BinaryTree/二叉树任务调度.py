from typing import List
from typing import Optional
from collections import defaultdict
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def minimalExecTime(self, root: TreeNode) -> float:
        def dfs(root: Optional[TreeNode]):
            if not root:
                return 0.0, 0.0
            a, b = dfs(root.left)
            c, d = dfs(root.right)
            if a < c:
                a, c = c, a
                b, d = d, b
            tc = root.val + a + c
            pc = 0
            if a - 2 * b > c:
                pc = b + c
            else:
                pc = (a + c) / 2
            return tc, pc

        tc, pc = dfs(root)
        return tc - pc


if __name__ == "__main__":
    root = TreeNode(47)
    root.left = TreeNode(74)
    root.right = TreeNode(31)
    print(Solution().minimalExecTime(root))
