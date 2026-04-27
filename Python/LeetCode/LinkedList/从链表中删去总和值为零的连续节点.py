from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def removeZeroSumSublists(self, head: Optional[ListNode]) -> Optional[ListNode]:
        seen = {}
        cur = dummy = ListNode(0, head)
        seen[0] = dummy
        prefix = 0
        while cur:
            prefix += cur.val
            seen[prefix] = cur
            cur = cur.next
        cur = dummy
        prefix = 0
        while cur:
            prefix += cur.val
            cur.next = seen[prefix].next
            cur = cur.next
        return dummy.next


if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(
        1, ListNode(2, ListNode(-3, ListNode(1, ListNode(3))))
    )
    list2 = ListNode(1, ListNode(2, ListNode(3)))
    lists = [list1, list2]
    a = 3
    b = 4
    result = solution.removeZeroSumSublists(list1)
    while result:
        print(result.val)
        result = result.next
