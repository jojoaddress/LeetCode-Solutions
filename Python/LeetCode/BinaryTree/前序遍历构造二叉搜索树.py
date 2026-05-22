from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution1:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:

        def dfs(l, r):
            if l > r:
                return None
            val = preorder[l]
            node = TreeNode(val)

            m = l + 1
            while m <= r and preorder[m] < val:
                m += 1

            node.left = dfs(l + 1, m - 1)
            node.right = dfs(m, r)
            return node

        return dfs(0, len(preorder) - 1)


class Solution:
    def bstFromPreorder(self, preorder: List[int]) -> Optional[TreeNode]:
        if not preorder:
            return None
        val = preorder[0]
        root = TreeNode(val)
        m = 1
        while m < len(preorder) and preorder[m] < val:
            m += 1
        root.left = self.bstFromPreorder(preorder[1:m])
        root.right = self.bstFromPreorder(preorder[m:])
        return root


if __name__ == "__main__":
    s = Solution()
    root = s.bstFromPreorder([8, 5, 1, 7, 10, 12])
    print(root.val)
