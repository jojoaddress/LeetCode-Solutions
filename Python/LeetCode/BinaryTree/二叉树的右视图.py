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
    # BFS
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        if root is None:
            return []
        ans = []
        q = deque([root])
        while q:
            lq = len(q)
            for i in range(lq):
                node = q.popleft()
                if i == lq - 1:
                    ans.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return ans

    # DFS
    def rightSideView1(self, root: Optional[TreeNode]) -> List[int]:
        ans = []

        def dfs(root: Optional[TreeNode], depth: int) -> None:
            if root is None:
                return
            if depth == len(ans):
                ans.append(root.val)
            dfs(root.right, depth + 1)
            dfs(root.left, depth + 1)

        dfs(root, 0)
        return ans


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(3), TreeNode(2))  # [1,2,3]
    result = solution.rightSideView(tree)
    for _, r in enumerate(result):
        print(r)
