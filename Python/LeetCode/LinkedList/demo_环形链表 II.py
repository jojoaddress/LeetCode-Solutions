from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


""" 
1.a:慢指针从head到入环口
2.b:慢指针从head到相遇点
3.c:环长度
4.快指针走了2b，2b-b=kc，k为多走的圈数，即b=kc
5.慢指针在圈中走的步数，b-a=kc-a,即慢指针走a步肯定能到入环口，同时头结点走a步也能到入环口，他俩能相遇
"""


class Solution:
    def detectCycle2(self, head: Optional[ListNode]) -> Optional[ListNode]:
        left = right = head
        while right and right.next:
            left = left.next
            right = right.next.next
            if left is right:
                while left is not head:
                    left = left.next
                    head = head.next
                return left
        return None

    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cnt = set()
        while head:
            if head in cnt:
                return head
            cnt.add(head)
            head = head.next
        return None


if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = head.next
    n = 5
    res = Solution().detectCycle(head)
    print(res.val)
