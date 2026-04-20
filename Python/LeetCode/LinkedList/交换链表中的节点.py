from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def swapNodes(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        dummy = ListNode(next=head)
        right = left = dummy
        for _ in range(k):
            right = right.next
        cur1 = right
        while right.next:
            right = right.next
            left = left.next
        cur2 = left.next

        # 交换
        if cur1.val != cur2.val:
            tmp = cur1.val
            cur1.val = cur2.val
            cur2.val = tmp

        return dummy.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    head.next.next.next.next.next = ListNode(6)
    n = 3
    res = Solution().swapNodes(head, n)
    while res:
        print(res.val)
        res = res.next
