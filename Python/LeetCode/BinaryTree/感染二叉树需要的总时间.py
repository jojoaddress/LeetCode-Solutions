from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def amountOfTime(self, root: Optional[TreeNode], start: int) -> int:
        res = 0
        def dfs(root:Optional[TreeNode])->tuple[int,bool]:
            if root is None:
                return 0,False
            left,lb = dfs(root.left)
            right,rb = dfs(root.right)
            nonlocal res
            if root.val == start:
                res = max(left,right)
                return 1,True
            if lb or rb:
                res = max(res,left+right)
                return (left if lb else right) +1,True
            return max(left,right)+1,False
        dfs(root)
        return res

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        1,
        TreeNode(5, None, None),
        TreeNode(3, TreeNode(10, None, None), TreeNode(6, None, None)),
    )  # [1,5,3,null,null,10,6]
    result = solution.amountOfTime(tree, 3)
    print(result)