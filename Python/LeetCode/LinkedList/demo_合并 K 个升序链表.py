from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeTwoList(self, l1: Optional[ListNode],l2: Optional[ListNode] ) -> Optional[ListNode]:
        cur = dummy = ListNode()
        while l1 and l2:
            if l1.val<=l2.val:
                cur.next = l1
                l1 = l1.next
            else:
                cur.next = l2
                l2 = l2.next
            cur = cur.next
        cur.next = l1 if l1 else l2
        return dummy.next
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        m = len(lists)
        if m == 0:
            return None
        if m==1:
            return lists[0]
        left = self.mergeKLists(lists[m//2:])
        right = self.mergeKLists(lists[:m//2])
        return self.mergeTwoList(left,right)
    
if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(1, ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5))))))
    list2 = ListNode(1, ListNode(2, ListNode(3)))
    lists = [list1,list2]
    a = 3
    b = 4
    result = solution.mergeKLists(lists)
    while result:
        print(result.val)
        result = result.next
        