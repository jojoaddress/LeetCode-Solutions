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
    def maxProduct(self, root: Optional[TreeNode]) -> int:
        MOD = 10**9 + 7

        def dfs1(root: Optional[TreeNode]) -> int:
            if root is None:
                return 0
            left = dfs1(root.left)
            right = dfs1(root.right)
            return root.val + left + right

        sum = dfs1(root)
        best = 0

        def dfs2(root: Optional[TreeNode]) -> int:
            if root is None:
                return 0
            left = dfs2(root.left)
            right = dfs2(root.right)
            num = left + right + root.val
            nonlocal best
            if abs(2 * num - sum) < abs(2 * best - sum):
                best = num
            return num

        dfs2(root)
        return (best * (sum - best)) % MOD


if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)
    print(Solution().maxProduct(root))
