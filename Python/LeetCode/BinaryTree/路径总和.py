from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def hasPathSum(self, root: Optional[TreeNode], targetSum: int) -> bool:
        def dfs(root: Optional[TreeNode], cur: int) -> bool:
            if not root:
                return False
            cur += root.val
            if not root.left and not root.right:
                return cur == targetSum
            return dfs(root.left,cur) or dfs(root.right,cur)

        return dfs(root, 0)


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.hasPathSum(tree, 6)
    print(result)
