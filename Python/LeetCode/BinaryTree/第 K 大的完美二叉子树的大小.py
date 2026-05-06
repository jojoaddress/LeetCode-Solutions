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
    def kthLargestPerfectSubtree(self, root: Optional[TreeNode], k: int) -> int:
        res = []

        def dfs(root: Optional[TreeNode]) -> tuple[bool, int]:
            if not root:
                return True, 0
            left_jud, left_num = dfs(root.left)
            right_jud, right_num = dfs(root.right)
            if not left_jud or not right_jud or left_num != right_num:
                return False, 0
            new_num = left_num + right_num + 1
            res.append(new_num)
            return True, new_num

        dfs(root)
        res.sort()
        return res[-k] if k <= len(res) else -1


if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)
    root.right.right = TreeNode(7)
    print(Solution().kthLargestPerfectSubtree(root, 1))
