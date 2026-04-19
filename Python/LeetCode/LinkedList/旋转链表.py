from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def rotateRight(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        left = right = head
        curlen = 0
        cur = head
        while cur:
            curlen += 1
            cur = cur.next
        if curlen == 0:
            return head
        k = k % curlen
        if k == 0:
            return head
        for _ in range(k):
            right = right.next
        while right.next:
            right = right.next
            left = left.next
        newHead = left.next
        left.next = None
        right.next = head
        return newHead


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    n = 5
    res = Solution().rotateRight(head, n)
    while res:
        print(res.val)
        res = res.next
