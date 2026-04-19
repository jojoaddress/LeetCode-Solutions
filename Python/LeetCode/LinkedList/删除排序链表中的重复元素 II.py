from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def deleteDuplicates(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = dummy = ListNode(next=head)
        while cur.next and cur.next.next:
            val = cur.next.val
            if cur.next.next.val == val:
                while cur.next and cur.next.val == val:
                    cur.next = cur.next.next
            else:
                cur = cur.next
        return dummy.next 

if __name__ == "__main__":
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(3, ListNode(3)))))
    nums = [1, 2, 3]
    res = Solution().deleteDuplicates(head)
    while res:
        print(res.val)
        res = res.next
