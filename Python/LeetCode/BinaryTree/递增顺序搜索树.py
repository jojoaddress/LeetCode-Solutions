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
    def increasingBST(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        list = []
        def dfs(root:Optional[TreeNode]):
            if not root:
                return
            dfs(root.left)
            list.append(root)
            dfs(root.right)
        dfs(root)
        pre = list[0]
        for x in list[1:]:
            x.left = None
            x.right = None
            pre.right = x
            pre = x
        return list[0]

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(5, TreeNode(3), TreeNode(6))  # [5,3,6]
    result = solution.increasingBST(tree)
    # Print the values of the resulting tree in order
    current = result
    while current:
        print(current.val)  # Output should be 3, 5, 6 in order
        current = current.right