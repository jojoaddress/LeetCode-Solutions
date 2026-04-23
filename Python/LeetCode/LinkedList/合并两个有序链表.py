from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def mergeTwoLists2(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        if list1 is None and list2 is None:
            return None
        tmp = 0
        if list1 and list2:
            if list1.val <= list2.val:
                tmp = list1.val
                list1 = list1.next
            else:
                tmp = list2.val
                list2 = list2.next
        elif list1:
            tmp = list1.val
            list1 = list1.next
        else:
            tmp = list2.val
            list2 = list2.next
        return ListNode(tmp,self.mergeTwoLists(list1,list2))
    
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        cur = dummy = ListNode()
        while list1 and list2:
            if list1.val <= list2.val:
                cur.next = ListNode(list1.val)
                list1 = list1.next
            else:
                cur.next = ListNode(list2.val)
                list2 = list2.next
            cur = cur.next
        cur.next = list1 if list1 else list2
        return dummy.next

if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(1, ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(1, ListNode(2, ListNode(3)))
    a = 3
    b = 4
    result = solution.mergeTwoLists(list1, list2)
    while result:
        print(result.val)
        result = result.next
