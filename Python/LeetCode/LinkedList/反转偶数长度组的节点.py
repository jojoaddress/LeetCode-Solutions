from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(
        self, head: Optional[ListNode], end: Optional[ListNode]
    ) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur != end:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def reverseEvenLengthGroups(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre = dummy = ListNode(next=head)
        cur = pre.next
        group = 1
        while cur:
            cnt = 0
            start = cur
            while cnt < group and cur:
                cur = cur.next
                cnt += 1
            if cnt != 0 and cnt % 2 == 0:
                newHead = self.reverseList(start, cur)
                pre.next = newHead
                start.next = cur
                pre = start
            else:
                tail = start
                for _ in range(cnt-1):
                    tail = tail.next
                pre = tail
            group += 1
        return dummy.next


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(5)
    head.next.next.next.next = ListNode(4)
    left = 2
    res = Solution().reverseEvenLengthGroups(head)
    while res:
        print(res.val)
        res = res.next
