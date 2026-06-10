from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isCousins(self, root: Optional[TreeNode], x: int, y: int) -> bool:
        father = depth = None
        def dfs(root:Optional[TreeNode],fa:Optional[TreeNode],d:int)->bool:
            if not root:
                return False
            if root.val == x or root.val == y:
                nonlocal father,depth
                if depth:
                    return d == depth and fa != father
                father,depth = fa,d
            return dfs(root.left,root,d+1) or dfs(root.right,root,d+1)
        return dfs(root,None,1)
        
if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)

    print(solution.isCousins(root, 4, 3))