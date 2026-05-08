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
    def pruneTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:

        def dfs(root: Optional[TreeNode]) -> bool:
            if root is None:
                return False
            left = dfs(root.left)
            right = dfs(root.right)

            if not left:
                root.left = None
            if not right:
                root.right = None

            return root.val == 1 or left or right

        return root if dfs(root) else None


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1)
    tree.left = TreeNode(0)
    tree.right = TreeNode(1)
    tree.left.left = TreeNode(0)
    tree.left.right = TreeNode(0)
    tree.right.right = TreeNode(1)
    tree.right.left = TreeNode(0)
    result = solution.pruneTree(tree)

    # 打印二叉树
    def print_tree(node):
        if node is None:
            return
        print(node.val)
        print_tree(node.left)
        print_tree(node.right)

    print_tree(result)
