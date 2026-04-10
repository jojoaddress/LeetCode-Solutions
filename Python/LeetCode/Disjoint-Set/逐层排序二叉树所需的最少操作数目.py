from typing import List, Optional
from collections import deque

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class UnionFind:
    def __init__(self,n:int):
        self._fa = list(range(n))
        self.cc = n

    def find(self,x:int)->int:
        fa = self._fa
        if fa[x] != x:
            fa[x] = self.find(fa[x])
        return fa[x]

    def union(self,x:int,y:int)->bool:
        x,y = self.find(x),self.find(y)
        if x==y:
            return False
        self._fa[x] = y
        self.cc -= 1

class Solution:
    def minimumOperations(self, root: Optional[TreeNode]) -> int:
        if not root:
            return 0
        res = 0
        queue = deque([root])
        while queue:
            level_size = len(queue)
            current_level = []
            for _ in range(level_size):
                node = queue.popleft()
                current_level.append(node.val)
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
            
            if current_level:
                nums = sorted((x,i) for i,x in enumerate(current_level))
                uf = UnionFind(len(current_level))
                for i,(_, x) in enumerate(nums):
                    uf.union(x,i)
                res += len(current_level) - uf.cc
        return res

if __name__ == "__main__":
    root = TreeNode(1)
    root.left = TreeNode(3)
    root.right = TreeNode(2)
    print(Solution().minimumOperations(root))

