from typing import List
from typing import Optional
from collections import defaultdict
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def convertBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        s = 0

        def dfs(root: Optional[TreeNode]) -> None:
            if not root:
                return
            dfs(root.right)
            nonlocal s
            s += root.val
            root.val = s
            dfs(root.left)

        dfs(root)
        return root


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(4)
    tree.left = TreeNode(2)
    tree.right = TreeNode(6)
    tree.left.left = TreeNode(1)
    tree.left.right = TreeNode(3)
    tree.right.left = TreeNode(5)
    tree.right.right = TreeNode(7)
    result = solution.convertBST(tree)

    # 打印二叉树
    def print_tree(node):
        if node is None:
            return
        print(node.val)
        print_tree(node.left)
        print_tree(node.right)

    print_tree(result)
