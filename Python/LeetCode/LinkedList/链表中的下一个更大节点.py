from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverse(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        pre = None
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def nextLargerNodes(self, head: Optional[ListNode]) -> List[int]:
        newHead = self.reverse(head)
        res = []
        st = []
        cur = newHead
        while cur:
            while st and st[-1] <= cur.val:
                st.pop()
            res.append(st[-1] if st else 0)
            st.append(cur.val)
            cur = cur.next
        return res[::-1]


if __name__ == "__main__":
    solution = Solution()
    list1 = ListNode(2, ListNode(7, ListNode(4, ListNode(3, ListNode(5, ListNode(5))))))
    list2 = ListNode(1, ListNode(2, ListNode(3)))
    lists = [list1, list2]
    a = 3
    b = 4
    result = solution.nextLargerNodes(list1)
    for res in result:
        print(res)
