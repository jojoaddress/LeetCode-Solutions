from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def addTwoNumbers2(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        cur = dummy = ListNode(0)
        tmp = 0
        while l1 and l2:
            num = (l1.val + l2.val + tmp) % 10
            cur.next = ListNode(num)
            tmp = (l1.val + l2.val + tmp) // 10
            cur = cur.next
            l1 = l1.next
            l2 = l2.next
        while l1:
            num = (l1.val +  tmp)%10
            cur.next = ListNode(num)
            tmp = (l1.val +  tmp) // 10
            cur = cur.next
            l1 = l1.next
        while l2:
            num = (l2.val +  tmp)%10
            cur.next = ListNode(num)
            tmp = (l2.val +  tmp) // 10
            cur = cur.next
            l2 = l2.next
        if tmp:
            cur.next = ListNode(tmp)
        return dummy.next
    
    def addTwoNumbers(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        dummy = cur = ListNode()
        carry = 0
        while l1 or l2 or carry:
            if l1:
                carry += l1.val
                l1=l1.next
            if l2:
                carry += l2.val
                l2 =l2.next
            cur.next = ListNode(carry%10)
            carry//=10
            cur = cur.next
        return dummy.next

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
