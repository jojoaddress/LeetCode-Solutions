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
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        res = 0
        def dfs(root:Optional[TreeNode])->int:
            if not root:
                return 0
            left = dfs(root.left)
            right = dfs(root.right)
            nonlocal res
            res = max(res,left+right)
            return max(left,right)+1
        dfs(root)
        return res
    
if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(
        1,
        TreeNode(2, TreeNode(4), TreeNode(5)),
        TreeNode(3, None, None),
    )  # [1,2,3,4,5]
    result = solution.diameterOfBinaryTree(tree)
    print(result)