from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverseList(self, head: Optional[ListNode],end: Optional[ListNode]) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur!=end:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        cur = dummy = ListNode(next=head)
        i = 0
        pre = None
        last = None
        while cur:
            if i==left-1:
                pre = cur
            if i==right+1:
                last = cur
            i+=1
            cur = cur.next
        tmpStart = pre.next
        tmptail = self.reverseList(tmpStart,last)
        pre.next = tmptail
        tmpStart.next = last
        return dummy.next

if __name__ == '__main__':
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    left = 2
    right = 4
    res = Solution().reverseBetween(head,left,right)
    while res:
        print(res.val)
        res = res.next
