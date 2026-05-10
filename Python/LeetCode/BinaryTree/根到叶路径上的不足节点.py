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
    def sufficientSubset(
        self, root: Optional[TreeNode], limit: int
    ) -> Optional[TreeNode]:
        limit -= root.val
        if not root.left and not root.right:
            return None if limit > 0 else root
        if root.left:
            root.left = self.sufficientSubset(root.left, limit)
        if root.right:
            root.right = self.sufficientSubset(root.right, limit)
        return root if root.left or root.right else None


if __name__ == "__main__":
    root = TreeNode(
        1,
        TreeNode(2, TreeNode(4), TreeNode(5)),
        TreeNode(3, TreeNode(6), TreeNode(7)),
    )
    limit = 7
    print(Solution().sufficientSubset(root, limit))
