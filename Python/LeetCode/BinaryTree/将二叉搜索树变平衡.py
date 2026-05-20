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
    def balanceBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        res = []
        def inorder(root:Optional[TreeNode]):
            if not root:
                return
            inorder(root.left)
            res.append(root.val)
            inorder(root.right)

        inorder(root)

        def build(l, r):
            if l > r: return None
            mid = (l + r) // 2
            node = TreeNode(res[mid])
            node.left = build(l, mid-1)
            node.right = build(mid+1, r)
            return node
        
        return build(0, len(res)-1)