from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def postorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        res = []

        def dfs(root: Optional[TreeNode]) -> None:
            if not root:
                return
            dfs(root.left)

            dfs(root.right)
            res.append(root.val)

        dfs(root)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.postorderTraversal(tree)
    for i in result:
        print(i)
