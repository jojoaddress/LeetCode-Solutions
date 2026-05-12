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


class Solution1:
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:
        res = []

        def dfs(root: Optional[TreeNode], temp: str) -> Optional[TreeNode]:
            if root is None:
                return None

            if not root.left and not root.right:
                temp = temp + str(root.val)
                res.append(temp)
            temp = temp + str(root.val) + "->"
            dfs(root.left, temp)
            dfs(root.right, temp)
            return root

        dfs(root, "")
        return res


class Solution:
    def binaryTreePaths(self, root: Optional[TreeNode]) -> List[str]:
        res = []
        path = []

        def dfs(root: Optional[TreeNode]) -> None:
            if root is None:
                return
            path.append(str(root.val))
            if not root.left and not root.right:
                res.append("->".join(path))
            else:
                dfs(root.left)
                dfs(root.right)
            path.pop()

        dfs(root)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(2, None, TreeNode(5)), TreeNode(3))  # [1,2,3,null,5]
    result = solution.binaryTreePaths(tree)
    print(result)
