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

    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        cur = left = right = head
        while right and right.next:
            right = right.next.next
            left = left.next
        newHead = self.reverse(left)
        while cur and newHead:
            if cur.val != newHead.val:
                return False
            cur = cur.next
            newHead = newHead.next
        return True


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(2)
    head.next.next.next = ListNode(1)

    n = 3

    print(Solution().isPalindrome(head))
