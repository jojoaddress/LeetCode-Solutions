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
    def smallestFromLeaf(self, root: Optional[TreeNode]) -> str:
        res = []
        def dfs(root:Optional[TreeNode],s:str)->None:
            if not root:
                return
            s = chr(ord('a') + root.val) + s
            if not root.left and not root.right:
                res.append(s)
            dfs(root.left,s)
            dfs(root.right,s)
        dfs(root,"")
        return min(res)

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(0, TreeNode(1, TreeNode(3), TreeNode(4)), TreeNode(2, TreeNode(3), TreeNode(4)))  # [0,1,2,3,4,3,4]
    result = solution.smallestFromLeaf(tree)
    print(result) 