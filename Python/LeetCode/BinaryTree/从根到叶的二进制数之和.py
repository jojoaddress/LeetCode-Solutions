from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:
        res = 0

        def dfs(root: Optional[TreeNode], num: int) -> None:
            if root is None:
                return
            num = (num << 1) + root.val
            if not root.left and not root.right:
                nonlocal res
                res += num
                return
            dfs(root.left, num)
            dfs(root.right, num)

        dfs(root, 0)
        return res

class Solution:
    def sumRootToLeaf(self, root: Optional[TreeNode]) -> int:
        def dfs(root:Optional[TreeNode])->int:
            if root is None:
                return 0
            if not root.left and not root.right:
                return root.val
            dfs(root.left)
if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(0)
    root.right = TreeNode(1)
    root.left.left = TreeNode(0)
    root.left.right = TreeNode(1)
    root.right.left = TreeNode(0)
    root.right.right = TreeNode(1)

    print(Solution().sumRootToLeaf(root))
