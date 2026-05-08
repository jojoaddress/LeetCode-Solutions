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
    def delNodes(
        self, root: Optional[TreeNode], to_delete: List[int]
    ) -> List[TreeNode]:
        res = []
        if root.val not in to_delete:
            res.append(root)

        def dfs(root: Optional[TreeNode], to_delete: List[int]) -> Optional[TreeNode]:
            if root is None:
                return None
            root.left = dfs(root.left, to_delete)
            root.right = dfs(root.right, to_delete)
            if root.val in to_delete:
                if root.left:
                    res.append(root.left)
                if root.right:
                    res.append(root.right)
                return None
            return root

        dfs(root, to_delete)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1)
    tree.left = TreeNode(2)
    tree.right = TreeNode(3)
    tree.left.left = TreeNode(4)
    tree.left.right = TreeNode(5)
    tree.right.left = TreeNode(6)
    tree.right.right = TreeNode(7)
    result = solution.delNodes(tree, [3, 5])

    # 打印二叉树
    def print_tree(node):
        if node is None:
            return
        print(node.val)
        print_tree(node.left)
        print_tree(node.right)

    for node in result:
        print_tree(node)
