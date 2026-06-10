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
    def widthOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        res = 1
        q = deque([(root,1)])
        while q:
            tmp = q
            q = deque()
            vis = []
            for node,index in tmp:
                vis.append([node,index])
                if node.left:
                    q.append([node.left,2*index])
                if node.right:
                    q.append([node.right,2*index+1])
            res = max(res,vis[-1][1]-vis[0][1]+1)
        return res
    
if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(1)
    root.left = TreeNode(3)
    root.right = TreeNode(2)
    root.left.left = TreeNode(5)

    print(solution.widthOfBinaryTree(root))