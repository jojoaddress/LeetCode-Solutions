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
    def searchBST(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        if root is None:
            return None
        if root.val > val:
            return self.searchBST(root.left, val)
        if root.val < val:
            return self.searchBST(root.right, val)
        return root


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        4, TreeNode(2, TreeNode(1), TreeNode(3)), TreeNode(7)
    )  # [4,2,7,1,3]
    result = solution.searchBST(tree, 2)
    print(result.val if result else None)
