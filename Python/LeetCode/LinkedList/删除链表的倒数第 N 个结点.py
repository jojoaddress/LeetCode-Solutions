from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverse(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def removeNthFromEnd2(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        newHead = self.reverse(head)
        pre = dummy = ListNode(next=newHead)
        cur = pre.next
        i = 1
        while cur:
            if i == n:
                pre.next = cur.next
                del cur
                break
            pre = cur
            cur = cur.next
            i += 1
        return self.reverse(dummy.next)

""" 
如果遇到需要删除头节点的题目，添加哨兵节点可以简化代码逻辑
"""
class Solution:
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        dummy = ListNode(next= head)
        left = right = dummy
        for _ in range(n):
            right = right.next
        while right.next:
            left = left.next
            right = right.next
        left.next = left.next.next
        return dummy.next
    
if __name__ == "__main__":
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    n = 2
    res = Solution().removeNthFromEnd(head,n)
    while res:
        print(res.val)
        res = res.next
