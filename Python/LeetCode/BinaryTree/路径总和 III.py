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
    def pathSum(self, root: Optional[TreeNode], targetSum: int) -> int:
        ans = 0
        cnt = defaultdict(int)
        cnt[0] = 1

        def dfs(root: Optional[TreeNode], s: int) -> None:
            if root is None:
                return

            s += root.val
            nonlocal ans
            ans += cnt[s - targetSum]

            cnt[s] += 1
            dfs(root.left, s)
            dfs(root.right, s)

            cnt[s] -= 1

        dfs(root, 0)
        return ans


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        10,
        TreeNode(
            5, TreeNode(3, TreeNode(3), TreeNode(-2)), TreeNode(2, None, TreeNode(1))
        ),
        TreeNode(-3, None, TreeNode(11)),
    )  # [10,5,-3,3,2,null,11,3,-2,null,1]
    targetSum = 8
    result = solution.pathSum(tree, targetSum)
    print(result)
