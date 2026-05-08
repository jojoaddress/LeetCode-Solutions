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
    def removeLeafNodes(
        self, root: Optional[TreeNode], target: int
    ) -> Optional[TreeNode]:
        if root is None:
            return None
        root.left = self.removeLeafNodes(root.left, target)
        root.right = self.removeLeafNodes(root.right, target)
        if root.left is None and root.right is None and root.val == target:
            return None
        return root


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1)
    tree.left = TreeNode(2)
    tree.right = TreeNode(3)
    tree.left.left = TreeNode(2)
    result = solution.removeLeafNodes(tree, 2)

    # 打印二叉树
    def print_tree(node):
        if node is None:
            return
        print(node.val)
        print_tree(node.left)
        print_tree(node.right)

    print_tree(result)
