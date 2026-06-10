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
    def distanceK(self, root: TreeNode, target: TreeNode, k: int) -> List[int]:
        if not root:
            return []
        graph = defaultdict(list)
        q = deque([root])
        while q:
            node = q.popleft()
            if node.left:
                graph[node.val].append(node.left.val)
                graph[node.left.val].append(node.val)
                q.append(node.left)
            if node.right:
                graph[node.val].append(node.right.val)
                graph[node.right.val].append(node.val)
                q.append(node.right)
        
        res = []
        q = deque([(target.val,0)])
        vis = set()
        while q:
            node,dist = q.popleft()
            vis.add(node)
            if dist == k:
                res.append(node)
            for neighbor in graph[node]:
                if neighbor not in vis:
                    q.append([neighbor,dist+1])
        return res