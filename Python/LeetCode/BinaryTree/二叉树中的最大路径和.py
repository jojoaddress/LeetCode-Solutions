from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def maxPathSum(self, root: Optional[TreeNode]) -> int:
        res = -inf

        def dfs(root: Optional[TreeNode]) -> int:
            if not root:
                return 0
            left = dfs(root.left)
            right = dfs(root.right)
            tmp = root.val
            if left > 0:
                tmp += left
            if right > 0:
                tmp += right
            nonlocal res
            res = max(res, tmp)
            return max(left, right, 0) + root.val
        dfs(root)
        return res 

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        -10,
        TreeNode(9, None, None),
        TreeNode(20, TreeNode(15, None, None), TreeNode(7, None, None)),
    )  # [-10,9,20,null,null,15,7]
    result = solution.maxPathSum(tree)
    print(result)
