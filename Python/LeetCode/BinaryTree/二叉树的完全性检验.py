from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def isCompleteTree(self, root: Optional[TreeNode]) -> bool:
        if not root:
            return True
        q = deque([root])
        jud = False
        while q:
            node = q.popleft()
            if not node:
                jud = True
            else:
                if jud:
                    return False
                q.append(node.left)
                q.append(node.right)
        return True
