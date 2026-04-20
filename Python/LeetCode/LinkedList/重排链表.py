from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverse(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def reorderList(self, head: Optional[ListNode]) -> None:
        """
        Do not return anything, modify head in-place instead.
        """
        left = right = dummy = ListNode(next=head)
        while right and right.next:
            left = left.next
            right = right.next.next
        new_head = self.reverse(left.next)
        left.next = None
        while head and new_head:
            nxt1 = head.next
            nxt2 = new_head.next

            head.next = new_head
            new_head.next = nxt1

            new_head = nxt2
            head = nxt1

        return dummy.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    # head.next.next.next.next = ListNode(5)
    n = 5
    res = Solution().reorderList(head)
    while res:
        print(res.val)
        res = res.next
