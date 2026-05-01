from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def sumNumbers(self, root: Optional[TreeNode]) -> int:
        res = []

        def dfs(root: Optional[TreeNode], cur: int) -> None:
            if not root:
                return
            cur = cur * 10 + root.val
            if not root.left and not root.right:
                res.append(cur)
                return
            return dfs(root.left, cur) or dfs(root.right, cur)

        dfs(root, 0)
        return sum(res)


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(3), TreeNode(2))  # [1,null,2,3]
    result = solution.sumNumbers(tree)
    print(result)
