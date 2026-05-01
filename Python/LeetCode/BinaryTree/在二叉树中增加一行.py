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
    def addOneRow(
        self, root: Optional[TreeNode], val: int, depth: int
    ) -> Optional[TreeNode]:
        if depth == 1:
            return TreeNode(val, root, None)
        q = deque([root])
        cdepth = 0
        while q:
            cdepth += 1
            for _ in range(len(q)):
                node = q.popleft()
                if cdepth == depth - 1:
                    node.left = TreeNode(val, node.left, None)
                    node.right = TreeNode(val, None, node.right)
                    return root
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return root


if __name__ == "__main__":
    root = TreeNode(4)
    root.left = TreeNode(2)
    root.right = TreeNode(6)
    root.left.left = TreeNode(3)
    root.left.right = TreeNode(1)
    root.right.left = TreeNode(5)

    res = Solution().addOneRow(root, 1, 2)
    # 层序输出
    q = deque([res])
    while q:
        node = q.popleft()
        print(node.val)
        if node.left:
            q.append(node.left)
        if node.right:
            q.append(node.right)
