from typing import List
from typing import Optional
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def numColor(self, root: TreeNode) -> int:
        cnt = defaultdict(int)

        def dfs(root: TreeNode) -> None:
            if not root:
                return

            cnt[root.val] += 1
            dfs(root.left)
            dfs(root.right)

        dfs(root)
        return len(cnt)


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, None, TreeNode(2, TreeNode(3), None))  # [1,null,2,3]
    result = solution.numColor(tree)
    print(result)
