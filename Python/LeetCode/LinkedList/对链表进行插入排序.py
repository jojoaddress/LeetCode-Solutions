from typing import List
from typing import Optional
from collections import defaultdict
import math

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def insertionSortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(next=head)
        last = dummy.next
        cur = last.next

        while cur:
            if cur.val >= last.val:
                last = cur
            else:
                pre = dummy
                while pre.next.val < cur.val:
                    pre = pre.next
                last.next = cur.next
                cur.next = pre.next
                pre.next = cur
            cur = last.next
        return dummy.next

if __name__ == "__main__":
    head = ListNode(4, ListNode(2, ListNode(1, ListNode(3))))
    nums = [18,6,10,3]
    res = Solution().insertionSortList(head)
    while res:
        print(res.val)
        res = res.next
            