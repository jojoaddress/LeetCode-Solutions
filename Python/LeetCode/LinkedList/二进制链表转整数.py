from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def getDecimalValue(self, head: Optional[ListNode]) -> int:
        res = 0
        while head:
            res = res << 1 | head.val
            head = head.next
        return res
    
if __name__ == "__main__":
    head = ListNode(1, ListNode(0, ListNode(1)))
    print(Solution().getDecimalValue(head))  # Output: 5
