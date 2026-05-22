from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


"""
1. 没有要删除的节点
2. 有，且只有左子树存在
3. 有，且只有右子树存在
4. 有，且左右子树都在存在
"""


class Solution1:
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        ans = []

        def inorder(root: Optional[TreeNode]):
            if not root:
                return
            inorder(root.left)
            ans.append(root.val)
            inorder(root.right)

        inorder(root)
        if key not in ans:
            return root
        ans.remove(key)

        def dfs(ans: list):
            if not ans:
                return None
            m = len(ans) // 2
            left = dfs(ans[:m])
            right = dfs(ans[m + 1 :])
            return TreeNode(ans[m], left, right)

        return dfs(ans)


class Solution:
    def deleteNode(self, root: Optional[TreeNode], key: int) -> Optional[TreeNode]:
        if not root:
            return None
        if root.val < key:
            root.right = self.deleteNode(root.right, key)
        if root.val > key:
            root.left = self.deleteNode(root.left, key)
        if root.val != key:
            return root
        if not root.left:
            return root.right
        if not root.right:
            return root.left
        node = root.left
        while node.right:
            node = node.right
        node.right = root.right
        return root.left


if __name__ == "__main__":
    root = TreeNode(5)
    root.left = TreeNode(3)
    root.right = TreeNode(6)
    root.left.left = TreeNode(2)
    root.left.right = TreeNode(4)
    root.right.right = TreeNode(7)

    key = 3
    root = Solution().deleteNode(root, key)
    print(root.val)
    print(root.left.val)
    print(root.right.val)
