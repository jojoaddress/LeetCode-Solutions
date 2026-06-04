from typing import List
from typing import Optional
from collections import defaultdict
from math import inf
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


from collections import deque
from typing import Optional


class Solution:
    def isEvenOddTree(self, root: Optional[TreeNode]) -> bool:
        if not root:
            return True
        q = deque([root])
        depth = 0
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            if depth & 1:  # 奇数层：偶数、严格递减
                for i in range(len(vis) - 1):
                    if vis[i] <= vis[i + 1] or vis[i] % 2 == 1:
                        return False
                if vis[-1] % 2 == 1:
                    return False
            else:  # 偶数层：奇数、严格递增
                for i in range(len(vis) - 1):
                    if vis[i] >= vis[i + 1] or vis[i] % 2 == 0:
                        return False
                if vis[-1] % 2 == 0:
                    return False
            depth += 1
        return True
