from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def partition(self, head: Optional[ListNode], x: int) -> Optional[ListNode]:
        left = dummy1 = ListNode(0, None)
        pre = dummy2 = ListNode(next=head)
        cur = head
        while cur:
            if cur.val < x:
                nxt = cur.next
                cur.next = None
                pre.next = nxt
                left.next = cur
                left = cur
                cur = nxt
            else:
                pre = cur
                cur = cur.next
        left.next = dummy2.next
        return dummy1.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(4)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(2)
    head.next.next.next.next = ListNode(5)
    head.next.next.next.next.next = ListNode(2)
    n = 3
    res = Solution().partition(head, n)
    while res:
        print(res.val)
        res = res.next
