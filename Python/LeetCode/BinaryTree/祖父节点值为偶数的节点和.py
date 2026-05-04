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
    def sumEvenGrandparent(self, root: Optional[TreeNode]) -> int:

        res = 0
        def dfs(root:Optional[TreeNode],fv=None,pv=None)->None:
            if not root:
                return
            
            if pv and pv.val %2 == 0:
                nonlocal res
                res += root.val
            pv = fv
            fv = root
            dfs(root.left,fv,pv)
            dfs(root.right,fv,pv)
        dfs(root)
        return res

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(6, TreeNode(7, TreeNode(2), TreeNode(7)), TreeNode(8, None, TreeNode(3)))  # [6,7,8,2,7,null,3]
    result = solution.sumEvenGrandparent(tree)
    print(result)