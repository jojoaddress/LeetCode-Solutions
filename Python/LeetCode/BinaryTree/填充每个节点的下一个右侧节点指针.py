from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class Node:
    def __init__(self, val: int = 0, left: 'Node' = None, right: 'Node' = None, next: 'Node' = None):
        self.val = val
        self.left = left
        self.right = right
        self.next = next

class Solution1:
    def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if not root:
            return None
        q = deque([root])
        while q:
            pre = None
            for _ in range(len(q)):
                node = q.popleft()
                if pre:
                    pre.next = node
                pre = node
                if node.left:
                    q.append(node.left)
                if node.right:
                    q.append(node.right)
        return root

class Solution:
    def connect(self, root: 'Optional[Node]') -> 'Optional[Node]':
        if not root:
            return None
        leftmost = root
        while leftmost.left:
            head = leftmost
            while head:
                head.left.next = head.right
                if head.next:
                    head.right.next = head.next.left
                head = head.next
            leftmost = leftmost.left
        return root
if __name__ == "__main__":
    s = Solution()
    root = Node(1)
    root.left = Node(2)
    root.right = Node(3)
    root.left.left = Node(4)
    root.left.right = Node(5)
    root.right.left = Node(6)
    root.right.right = Node(7)
    s.connect(root)
    for node in [root, root.left, root.right, root.left.left, root.left.right, root.right.left, root.right.right]:
        print(node.val, node.next.val if node.next else None)