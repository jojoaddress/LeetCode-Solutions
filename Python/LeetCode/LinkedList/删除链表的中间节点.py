from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def deleteMiddle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre = dummy = ListNode(next=head)
        left = right = head
        while right and right.next:
            pre = left
            left = left.next
            right = right.next.next
        pre.next = left.next
        return dummy.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)

    n = 3
    res = Solution().deleteMiddle(head)
    while res:
        print(res.val)
        res = res.next
