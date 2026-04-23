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
    def addList(self, l1: Optional[ListNode], l2: Optional[ListNode],carry:int) -> Optional[ListNode]:
        if l1 is None and l2 is None and carry == 0:
            return None
        s = carry
        if l1:
            s+=l1.val
            l1=l1.next
        if l2:
            s+=l2.val
            l2=l2.next
        return ListNode(s%10,self.addList(l1,l2,s//10))

    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        newl1 = self.reverse(l1)
        newl2 = self.reverse(l2)
        newHead = self.addList(newl1,newl2,0)
        return self.reverse(newHead)

if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(1, ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(9, ListNode(2, ListNode(3)))
    a = 3
    b = 4
    result = solution.addTwoNumbers(list1, list2)
    while result:
        print(result.val)
        result = result.next