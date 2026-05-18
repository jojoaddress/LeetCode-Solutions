from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate
from math import inf

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def recoverTree(self, root: Optional[TreeNode]) -> None:
        list = []
        def dfs(root:Optional[TreeNode])->None:
            if not root:
                return
            dfs(root.left)
            list.append(root)
            dfs(root.right)

        dfs(root)
        n = len(list)
        left = right = -1
        for i in range(n-1):
            if list[i].val > list[i+1].val:
                left = i
                break
        
        if left == -1:
            return
        
        for j in range(n-1,0,-1):
            if list[j].val < list[j-1].val:
                right = j
                break
        list[left].val ,list[right].val = list[right].val, list[left].val
        return

if __name__ == "__main__":
    solution = Solution()
    tree = TreeNode(1, TreeNode(3), None)  # [1,3,null]
    tree.left.val, tree.val = tree.val, tree.left.val  # Swap values to create the problem
    solution.recoverTree(tree)
    print(tree.val)  # Output should be 3
    print(tree.left.val)  # Output should be 1