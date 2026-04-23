from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverse(self,head:Optional[ListNode])->Optional[ListNode]:
        pre = None
        cur =head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre
    def mulList(self, l1: Optional[ListNode],carry:int) -> Optional[ListNode]:
        cur=dummy = ListNode()
        while l1 or carry:
            if l1:
                carry += l1.val*2
                l1 = l1.next
            cur.next = ListNode(carry%10)
            carry//=10
            cur = cur.next
        return dummy.next
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        newl1 = self.reverse(head)
        newHead = self.mulList(newl1,0)
        return self.reverse(newHead)
    
if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(1, ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(9, ListNode(2, ListNode(3)))
    a = 3
    b = 4
    result = solution.doubleIt(list1)
    while result:
        print(result.val)
        result = result.next