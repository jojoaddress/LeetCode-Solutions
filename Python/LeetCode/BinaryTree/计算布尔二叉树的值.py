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
    def evaluateTree(self, root: Optional[TreeNode]) -> bool:
        if not root.left and not root.right:
            return True if root.val == 1 else False
        left = self.evaluateTree(root.left)
        right = self.evaluateTree(root.right)
        return left and right if root.val == 3 else left or right
    
if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(3)
    root.left = TreeNode(1)
    root.right = TreeNode(0)

    print(solution.evaluateTree(root))
            