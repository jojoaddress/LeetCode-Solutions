from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# 错误想法，每层的和，不能偷相邻的两层
class Solution1:
    def rob(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        q = deque([root])
        nums = []
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            nums.append(sum(vis))
        n = len(nums)
        dp = (n + 1) * [0]
        dp[1] = nums[0]
        for i in range(2, n + 1):
            dp[i] = max(dp[i - 1], dp[i - 2] + nums[i - 1])
        return dp[n]


class Solution:
    def rob(self, root: Optional[TreeNode]) -> int:

        def dfs(root: Optional[TreeNode]) -> tuple[int, int]:
            if not root:
                return (0, 0)  # 偷当前的最大值，不偷当前的最大值
            left = dfs(root.left)
            right = dfs(root.right)
            rob = root.val + left[1] + right[1]
            not_rob = max(left) + max(right)
            return (rob, not_rob)

        return max(dfs(root))


if __name__ == "__main__":
    root = TreeNode(3)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.right = TreeNode(3)
    root.right.right = TreeNode(1)
    print(Solution().rob(root))
