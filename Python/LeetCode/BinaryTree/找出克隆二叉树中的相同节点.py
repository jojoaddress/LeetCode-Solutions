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
    def getTargetCopy(
        self, original: TreeNode, cloned: TreeNode, target: TreeNode
    ) -> TreeNode:
        if not original or not cloned:
            return None
        if original is target:
            return cloned
        return self.getTargetCopy(original.left, cloned.left, target) or self.getTargetCopy(original.right, cloned.right, target)


if __name__ == "__main__":
    solution = Solution()
    original = TreeNode(7)
    original.left = TreeNode(4)
    original.right = TreeNode(3)
    original.right.left = TreeNode(6)
    original.right.right = TreeNode(19)

    cloned = TreeNode(7)
    cloned.left = TreeNode(4)
    cloned.right = TreeNode(3)
    cloned.right.left = TreeNode(6)
    cloned.right.right = TreeNode(19)

    target = original.right

    print(solution.getTargetCopy(original, cloned, target).val)
