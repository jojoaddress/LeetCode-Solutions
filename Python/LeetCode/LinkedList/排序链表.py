from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeTwoList(
        self, l1: Optional[ListNode], l2: Optional[ListNode]
    ) -> Optional[ListNode]:
        cur = dummy = ListNode()
        while l1 and l2:
            if l1.val <= l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next
            cur = cur.next
        cur.next = l1 if l1 else l2
        return dummy.next

    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head
        slow = head
        fast = head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        mid = slow.next
        slow.next = None
        left = self.sortList(head)
        right = self.sortList(mid)
        return self.mergeTwoList(left, right)


if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(1, ListNode(5, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(1, ListNode(2, ListNode(3)))
    lists = [list1, list2]
    a = 3
    b = 4
    result = solution.sortList(list1)
    while result:
        print(result.val)
        result = result.next
