from typing import List
from typing import Optional
from collections import deque
from collections import defaultdict


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# 层序遍历
class Solution:
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        if root is None:
            return []
        ans = []
        q = deque([root])
        while q:
            vis = []
            for _ in range(len(q)):
                node = q.popleft()
                vis.append(node.val)
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
            ans.append(vis)
        return ans


if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(3), TreeNode(2))  # [1,null,2,3]
    result = solution.levelOrder(tree)
    for _, r in enumerate(result):
        print(r)
