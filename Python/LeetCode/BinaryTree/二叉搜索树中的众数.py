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
    def findMode(self, root: Optional[TreeNode]) -> List[int]:
        cnt = defaultdict(int)

        def dfs(root: Optional[TreeNode]):
            if not root:
                return
            dfs(root.left)
            cnt[root.val] += 1
            dfs(root.right)

        dfs(root)
        maxV = max(cnt.values())
        res = [v for v, x in cnt.items() if x == maxV]
        return res
