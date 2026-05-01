from typing import List
from typing import Optional
from collections import defaultdict
from math import inf


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# 自顶向下
class Solution1:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        ans = inf

        def dfs(root: Optional[TreeNode], cnt: int) -> None:
            if not root:
                return
            cnt += 1
            if not root.left and not root.right:
                nonlocal ans
                ans = min(ans, cnt)
            dfs(root.left, cnt)
            dfs(root.right, cnt)

        dfs(root, 0)
        return 0 if ans == inf else ans


# 自底向上
class Solution:
    def minDepth(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        if not root.left:
            return self.minDepth(root.right) + 1
        if not root.right:
            return self.minDepth(root.left) + 1
        return min(self.minDepth(root.left), self.minDepth(root.right)) + 1


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.minDepth(tree)
    print(result)
