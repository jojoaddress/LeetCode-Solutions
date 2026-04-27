from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def getIntersectionNode2(
        self, headA: ListNode, headB: ListNode
    ) -> Optional[ListNode]:
        cnt = set()
        while headA:
            cnt.add(headA)
            headA = headA.next
        while headB:
            if headB in cnt:
                return headB
            headB = headB.next
        return None

    def getIntersectionNode(
        self, headA: ListNode, headB: ListNode
    ) -> Optional[ListNode]:
        p = headA
        q = headB
        while p is not q:
            p = p.next if p else headB
            q = q.next if q else headA
        return p


if __name__ == "__main__":
    headA = ListNode(1)
    headA.next = ListNode(9)
    headA.next.next = ListNode(1)
    headA.next.next.next = ListNode(2)
    headA.next.next.next.next = ListNode(4)

    headB = ListNode(3)
    # headB.next = ListNode(2)
    headB.next = headA.next.next.next
    # headB.next = headA.next.next.next

    res = Solution().getIntersectionNode(headA, headB)
    print(res.val if res else None)
