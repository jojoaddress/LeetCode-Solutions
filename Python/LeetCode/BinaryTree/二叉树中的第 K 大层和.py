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


class Solution:
    def kthLargestLevelSum(self, root: Optional[TreeNode], k: int) -> int:
        if not root:
            return 0
        q = deque([root])
        res = []
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            res.append(sum(vis))
        res.sort(reverse=True)
        return res[k - 1] if k <= len(res) else -1


if __name__ == "__main__":
    root = TreeNode(5)
    root.left = TreeNode(8)
    root.right = TreeNode(9)
    print(Solution().kthLargestLevelSum(root, 1))
