from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeNodes(self, head: Optional[ListNode]) -> Optional[ListNode]:
        resHead = ListNode(0)
        resCurrent = resHead
        tmp = 0
        if head.val != 0:
            return resHead
        head = head.next
        while head:
            if head.val != 0:
                tmp += head.val
            else:
                resCurrent.next = ListNode(tmp)
                resCurrent = resCurrent.next
                tmp = 0
            head = head.next
        return resHead.next


if __name__ == "__main__":
    head = ListNode(
        0,
        ListNode(
            3,
            ListNode(
                1, ListNode(0, ListNode(4, ListNode(5, ListNode(2, ListNode(0)))))
            ),
        ),
    )
    res = Solution().mergeNodes(head)
    while res:
        print(res.val)  # Output: 4 11
        res = res.next
