from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sumOfLeftLeaves(self, root: Optional[TreeNode]) -> int:

        def dfs(root:Optional[TreeNode])->int:
            if not root:
                return 0
            val = 0
            if root.left and not root.left.left and not root.left.right:
                val += root.left.val
            return dfs(root.left)+dfs(root.right)+val
            
        return dfs(root)

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.sumOfLeftLeaves(tree)
    print(result)