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
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:

        def dfs(l:Optional[TreeNode],r:Optional[TreeNode])->bool:
            if not l and not r:
                return True
            if not l:
                return False
            if not r:
                return False
            return l.val == r.val and dfs(l.left,r.right) and dfs(l.right,r.left)
        
        return dfs(root.left,root.right)

if __name__ == "__main__":
    root1 = TreeNode(1)
    root1.left = TreeNode(2)
    root1.right = TreeNode(2)


    print(Solution().isSymmetric(root1))