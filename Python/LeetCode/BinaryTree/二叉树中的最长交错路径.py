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
    def longestZigZag(self, root: Optional[TreeNode]) -> int:
        res = 0

        def dfs(root: Optional[TreeNode], pre: int, tmp: int) -> None:
            if not root:
                return
            nonlocal res
            res = max(res, tmp)
            if pre == 0:
                dfs(root.right, 1, tmp + 1)
                dfs(root.left, 0, 1)
            else:
                dfs(root.left, 0, tmp + 1)
                dfs(root.right, 1, 1)

        if root:
            dfs(root.left, 0, 1)
            dfs(root.right, 1, 1)
        return res


if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.right = TreeNode(4)
    root.left.right.right = TreeNode(5)

    print(Solution().longestZigZag(root))
