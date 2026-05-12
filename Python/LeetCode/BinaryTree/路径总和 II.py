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
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> List[List[int]]:
        res = []
        path = []

        def dfs(root: Optional[TreeNode], target: int) -> None:
            if root is None:
                return
            target -= root.val
            path.append(root.val)
            if not root.left and not root.right and target == 0:
                res.append(path[:])
            else:
                dfs(root.left, target)
                dfs(root.right, target)
            path.pop()
            target += root.val

        dfs(root, targetSum)
        return res


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        5,
        TreeNode(4, TreeNode(11, TreeNode(7), TreeNode(2))),
        TreeNode(8, TreeNode(13), TreeNode(4, TreeNode(5), TreeNode(1))),
    )  # [5,4,8,11,null,13,4,7,2,null,null,null,null,5,1]
    targetSum = 22
    result = solution.pathSum(tree, targetSum)
    print(result)
