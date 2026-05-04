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
    def goodNodes(self, root: Optional[TreeNode]) -> int:

        res = 0

        def dfs(root: Optional[TreeNode], maxVal: int):
            if not root:
                return
            if root.val >= maxVal:
                nonlocal res
                res += 1
                maxVal = max(maxVal, root.val)
                
            dfs(root.left, maxVal)
            dfs(root.right, maxVal)

        dfs(root, root.val)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        3, TreeNode(1, TreeNode(3), None), TreeNode(4, TreeNode(1), TreeNode(5))
    )  # [3,1,4,3,null,1,5]
    result = solution.goodNodes(tree)
    print(result)
