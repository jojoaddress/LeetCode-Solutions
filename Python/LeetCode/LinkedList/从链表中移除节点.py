from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverse(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        pre = None
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def removeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head = self.reverse(head)
        while cur.next:
            if cur.next.val < cur.val:
                cur.next = cur.next.next
            else:
                cur = cur.next
        return self.reverse(head)


if __name__ == "__main__":
    head = ListNode(5, ListNode(2, ListNode(13, ListNode(3, ListNode(8)))))
    k = 5
    res = Solution().removeNodes(head)
    while res:
        print(res.val)
        res = res.next
