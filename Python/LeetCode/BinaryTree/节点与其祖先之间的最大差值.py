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


# 自顶向下
class Solution1:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:

        diff = 0

        def dfs(root: Optional[TreeNode], minNum: int, maxNum: int) -> None:
            if not root:
                return 0
            minNum = min(minNum, root.val)
            maxNum = max(maxNum, root.val)

            nonlocal diff
            diff = max(diff, abs(minNum - root.val), abs(maxNum - root.val))
            dfs(root.left, minNum, maxNum)
            dfs(root.right, minNum, maxNum)

        dfs(root, root.val, root.val)
        return diff


# 自下向上
class Solution:
    def maxAncestorDiff(self, root: Optional[TreeNode]) -> int:
        diff = 0

        def dfs(root: Optional[TreeNode]) -> tuple[int, int]:
            if not root:
                return inf, -inf
            minLeft, maxLeft = dfs(root.left)
            minRight, maxRight = dfs(root.right)

            minNum = min(root.val,minLeft, minRight)
            maxNum = max(root.val,maxLeft, maxRight)

            nonlocal diff
            diff = max(diff, abs(root.val - minNum), abs(root.val - maxNum))

            return minNum, maxNum

        dfs(root)
        return diff


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        8,
        TreeNode(3, TreeNode(1), TreeNode(6, TreeNode(4), TreeNode(7))),
        TreeNode(10, None, TreeNode(14, TreeNode(13), None)),
    )  # [8,3,10,1,6,null,14,null,null,4,7,null,null,13,null,null]
    result = solution.maxAncestorDiff(tree)
    print(result)
