from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution1:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        res = True
        def dfs(root:Optional[TreeNode])->int:
            nonlocal res
            if root is None:
                return 0
            left = dfs(root.left)
            right = dfs(root.right)
            if abs(left-right) > 1:
                res = False
                return 0
            if not res:
                return 0
            return max(left,right)+1
        dfs(root)
        return res

class Solution:
    def isBalanced(self, root: Optional[TreeNode]) -> bool:
        if root is None:
            return True
        left = self.isBalanced(root.left)
        right = self.isBalanced(root.right)
        if not left or not right:
            return False
        left_depth = self.getDepth(root.left)
        right_depth = self.getDepth(root.right)
        if abs(left_depth-right_depth) > 1:
            return False
        return True
    
if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.right.left = TreeNode(15)
    root.right.right = TreeNode(7)

    print(solution.isBalanced(root))
