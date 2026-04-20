from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        left = right = head
        while right and right.next:
            left = left.next
            right = right.next.next
            if left is right:
                return True
        return False
