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
    def pseudoPalindromicPaths(self, root: Optional[TreeNode]) -> int:
        ans = 0
        cnt = defaultdict(int)

        def dfs(root: Optional[TreeNode]) -> None:
            nonlocal ans
            if root is None:
                return
            cnt[root.val] += 1
            if not root.left and not root.right:
                odd_count = sum(1 for v in cnt.values() if v % 2 == 1)
                if odd_count < 2:
                    ans += 1
            else:
                dfs(root.left)
                dfs(root.right)

            cnt[root.val] -= 1

        dfs(root)
        return ans

if __name__ == "__main__":
    