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
        if root in (None,p,q):
            return root
        left = self.lowestCommonAncestor(root.left,p,q)
        right = self.lowestCommonAncestor(root.right,p,q)
        if left and  right:
            return root
        if left:
            return left
        if right:
            return right
        return None
    
if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(2), TreeNode(3))  # [1,2,3]
    p = tree.left  # Node with value 2
    q = tree.right  # Node with value 3
    result = solution.lowestCommonAncestor(tree, p, q)
    print(result.val)  # Output should be 1, as the LCA of nodes 2 and 3 is node 1