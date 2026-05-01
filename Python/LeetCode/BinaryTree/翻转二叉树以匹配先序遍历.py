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
    def flipMatchVoyage(self, root: Optional[TreeNode], voyage: List[int]) -> List[int]:
        tag = True
        idx = 0
        ans = []

        def dfs(root: Optional[TreeNode]) -> None:
            nonlocal tag
            nonlocal idx
            if not root:
                return
            if root.val != voyage[idx]:
                tag = False
                return
            if not tag:
                return
            idx += 1
            if root.left and root.right and root.left.val != voyage[idx]:
                dfs(root.right)
                dfs(root.left)
                ans.append(root.val)
            else:
                dfs(root.left)
                dfs(root.right)

        dfs(root)
        return [-1] if not tag else ans


if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)

    print(Solution().flipMatchVoyage(root, [1, 3, 2]))
