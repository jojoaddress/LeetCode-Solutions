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
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        res = []

        def dfs(root: Optional[TreeNode]) -> None:
            if not root:
                return
            dfs(root.left)
            res.append(root.val)
            dfs(root.right)

        dfs(root)
        return res[k - 1]


if __name__ == "__main__":
    root = TreeNode(3)
    root.left = TreeNode(1)
    root.right = TreeNode(4)
    root.left.right = TreeNode(2)
    k = 1
    print(Solution().kthSmallest(root, k))
