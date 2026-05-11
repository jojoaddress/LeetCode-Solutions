from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def longestUnivaluePath(self, root: Optional[TreeNode]) -> int:
        res = 0

        def dfs(root: Optional[TreeNode]) -> tuple[Optional[TreeNode], int]:
            if root is None:
                return None, 0
            leftNode, leftLen = dfs(root.left)
            rightNode, rightLen = dfs(root.right)
            nonlocal res
            leftPath = leftLen + 1 if leftNode and leftNode.val == root.val else 0
            rightPath = rightLen + 1 if rightNode and rightNode.val == root.val else 0
            res = max(res, leftPath + rightPath)
            return root, max(leftPath, rightPath)

        dfs(root)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        5, TreeNode(4, TreeNode(1), TreeNode(1)), TreeNode(5, None, TreeNode(5))
    )  # [5,4,5,1,1,5]
    result = solution.longestUnivaluePath(tree)
    print(result)
