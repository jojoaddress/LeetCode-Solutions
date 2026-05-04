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
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if root is None:
            return 0
        return max(self.maxDepth(root.left),self.maxDepth(root.right))+1

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        8,
        TreeNode(3, TreeNode(1), TreeNode(6, TreeNode(4), TreeNode(7))),
        TreeNode(10, None, TreeNode(14, TreeNode(13), None)),
    )  # [8,3,10,1,6,null,14,null,null,4,7,null,null,13,null,null]
    result = solution.maxDepth(tree)
    print(result)