from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def findBottomLeftValue(self, root: Optional[TreeNode]) -> int:
        q = deque([root])
        res = 0
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            res = vis[0]
        return res

if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(2)
    root.left = TreeNode(1)
    root.right = TreeNode(3)

    print(solution.findBottomLeftValue(root))