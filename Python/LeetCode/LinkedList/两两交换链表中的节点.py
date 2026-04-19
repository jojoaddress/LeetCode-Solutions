from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = dummy = ListNode(next=head)
        while cur and cur.next and cur.next.next:
            tmpStart = cur.next
            tmpTail = cur.next.next
            nxt = tmpTail.next
            cur.next = tmpTail
            tmpTail.next = tmpStart
            tmpStart.next = nxt
            cur = tmpStart
        return dummy.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    left = 2
    right = 4
    res = Solution().swapPairs(head)
    while res:
        print(res.val)
        res = res.next
