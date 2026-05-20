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
    def insertIntoMaxTree(self, root: Optional[TreeNode], val: int) -> Optional[TreeNode]:
        def dfs(root:Optional[TreeNode]):
            if not root:
                return TreeNode(val)
            if root.val < val:
                return TreeNode(val,root,None)
            root.right = dfs(root.right)
            return root
        return dfs(root)