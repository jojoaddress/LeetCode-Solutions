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

    def closestNodes(
        self, root: Optional[TreeNode], queries: List[int]
    ) -> List[List[int]]:
        ans = [[-1, -1] for _ in range(len(queries))]
        inorder = []

        def dfs(root: Optional[TreeNode]):
            if not root:
                return
            dfs(root.left)
            inorder.append(root.val)
            dfs(root.right)

        dfs(root)

        import bisect

        for i, q in enumerate(queries):
            idx = bisect.bisect_right(inorder, q) - 1
            if idx >= 0:
                ans[i][0] = inorder[idx]
            idx = bisect.bisect_left(inorder, q)
            if idx < len(inorder):
                ans[i][1] = inorder[idx]
        return ans


if __name__ == "__main__":
    root = TreeNode(6, TreeNode(2, TreeNode(0), TreeNode(4)), TreeNode(7))
    queries = [2, 5, 8]
    print(Solution().closestNodes(root, queries))
