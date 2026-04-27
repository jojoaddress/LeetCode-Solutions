from typing import List
from typing import Optional
from collections import defaultdict

class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random


class Solution:
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        cur = head
        while cur:
            cur.next = Node(cur.val,cur.next)
            cur = cur.next.next
        cur = head
        while cur:
            if cur.random:
                cur.next.random = cur.random.next
            cur = cur.next.next
        
        tail = dummy = Node(0,next=head)
        cur = head
        while cur:
            copy = cur.next
            cur.next = copy.next
            tail.next = copy
            cur = cur.next
            tail = tail.next
        return dummy.next

if __name__ == "__main__": 
    head = Node(7)
    head.next = Node(13)
    head.next.next = Node(11)
    head.next.next.next = Node(10)
    head.next.next.next.next = Node(1)
    head.random = None
    head.next.random = head
    head.next.next.random = head.next.next.next.next
    head.next.next.next.random = head.next.next
    head.next.next.next.next.random = head
    solution = Solution()
    copy_head = solution.copyRandomList(head)
    while copy_head:
        print(copy_head.val)
        copy_head = copy_head.next