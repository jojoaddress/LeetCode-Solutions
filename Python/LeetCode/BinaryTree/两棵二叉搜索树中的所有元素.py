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
    def inorder_collect(self, root):
        res = []

        def dfs(root: Optional[TreeNode]) -> None:
            if not root:
                return
            dfs(root.left)
            res.append(root.val)
            dfs(root.right)

        dfs(root)
        return res

    def getAllElements(
        self, root1: Optional[TreeNode], root2: Optional[TreeNode]
    ) -> List[int]:
        res1 = self.inorder_collect(root1)
        res2 = self.inorder_collect(root2)
        i = j = 0
        res = []
        while i < len(res1) and j < len(res2):
            if res1[i] <= res2[j]:
                res.append(res1[i])
                i += 1
            else:
                res.append(res2[j])
                j += 1
        res.extend(res1[i:])
        res.extend(res2[j:])
        return res


if __name__ == "__main__":
    root1 = TreeNode(2, TreeNode(1), TreeNode(4))
    root2 = TreeNode(1, TreeNode(0), TreeNode(3))
    print(Solution().getAllElements(root1, root2))
