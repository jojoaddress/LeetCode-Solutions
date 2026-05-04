from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def isUnivalTree(self, root: Optional[TreeNode]) -> bool:

        def dfs(root:Optional[TreeNode],val:int)->bool:
            if root is None:
                return True
            if root.val != val:
                return False
            return dfs(root.left,val) and dfs(root.right,val)
        return dfs(root,root.val)

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(1, TreeNode(1), None))  # [1,null,2,3]
    result = solution.isUnivalTree(tree)
    print(result)