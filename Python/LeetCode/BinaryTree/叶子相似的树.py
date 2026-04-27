from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def leafSimilar(self, root1: Optional[TreeNode], root2: Optional[TreeNode]) -> bool:
        res1 = []
        res2 = []

        def dfs(root: Optional[TreeNode], res: List) -> None:
            if not root:
                return
            if not root.left and not root.right:
                res.append(root.val)
                return
            dfs(root.left, res)
            dfs(root.right, res)

        dfs(root1, res1)
        dfs(root2, res2)
        return res1[:] == res2[:]


if __name__ == "__main__":
    solution = Solution()
    tree1 = TreeNode(
        3,
        TreeNode(5, TreeNode(6), TreeNode(2, TreeNode(7), TreeNode(4))),
        TreeNode(1, TreeNode(9), TreeNode(8)),
    )
    tree2 = TreeNode(
        3,
        TreeNode(5, TreeNode(6), TreeNode(7)),
        TreeNode(1, TreeNode(4), TreeNode(2, TreeNode(9), TreeNode(8))),
    )
    result = solution.leafSimilar(tree1, tree2)
    print(result)
