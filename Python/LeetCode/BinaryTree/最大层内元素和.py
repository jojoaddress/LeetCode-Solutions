from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def maxLevelSum(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        q = deque([root])
        res = 1
        depth = 1
        maxNum = root.val
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            sumNum = sum(vis)
            if sumNum > maxNum:
                maxNum = sumNum
                res = depth
            depth += 1
        return res

if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(3)
    root.left = TreeNode(9)
    root.right = TreeNode(20)
    root.left.left = TreeNode(15)

    print(solution.maxLevelSum(root))