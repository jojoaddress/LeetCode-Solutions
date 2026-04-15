from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeInBetween(
        self, list1: ListNode, a: int, b: int, list2: ListNode
    ) -> ListNode:
        cur = list1
        cut1 = None
        cut2 = None
        i = 0
        while cur:
            if i == a - 1:
                cut1 = cur
            if i == b + 1:
                cut2 = cur
            i += 1
            cur = cur.next

        cur = list2
        while cur.next:
            cur = cur.next
        cut1.next = list2
        cur.next = cut2
        return list1


if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(0, ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(1000000, ListNode(1000001, ListNode(1000002)))
    a = 3
    b = 4
    result = solution.mergeInBetween(list1, a, b, list2)
    while result:
        print(result.val)
        result = result.next
