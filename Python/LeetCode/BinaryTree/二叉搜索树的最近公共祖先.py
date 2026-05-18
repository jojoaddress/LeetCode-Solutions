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
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        x = root.val
        if p.val < x and q.val <x:
            return self.lowestCommonAncestor(root.left,p,q)
        if p.val > x and q.val > x:
            return self.lowestCommonAncestor(root.right,p,q)
        return root
      

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(6, TreeNode(2), TreeNode(8))  # [6,2,8]
    p = tree.left  # Node with value 2
    q = tree.right  # Node with value 8
    result = solution.lowestCommonAncestor(tree, p, q)
    print(result.val)  # Output should be 6, as the LCA of nodes 2 and 8 is node 6