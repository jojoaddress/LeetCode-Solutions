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
    def findSecondMinimumValue(self, root: Optional[TreeNode]) -> int:
        res = inf
        def dfs(node:Optional[TreeNode])->None:
            if not node:
                return
            if node.val>root.val:
                nonlocal res
                res = min(res,node.val)
            dfs(node.left)
            dfs(node.right)
        dfs(root)
        return -1 if res==inf else res
        
if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.findSecondMinimumValue(tree)
    print(result)