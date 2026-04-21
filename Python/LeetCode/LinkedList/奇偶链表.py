from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def oddEvenList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if head == None or head.next == None:
            return head
        left = head
        rightHead = right = head.next
        while right and right.next:
            left.next = right.next
            left = left.next
            right.next = left.next
            right = right.next
        left.next = rightHead
        return head


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    head.next.next.next.next.next = ListNode(6)
    n = 5
    res = Solution().oddEvenList(head)
    while res:
        print(res.val)
        res = res.next
