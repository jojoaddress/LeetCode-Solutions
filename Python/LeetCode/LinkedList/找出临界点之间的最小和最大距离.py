from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def nodesBetweenCriticalPoints(self, head: Optional[ListNode]) -> List[int]:
        first = -1
        last = -1
        ans = [float('inf'), -1]
        pre = head
        i = 0
        while head.next:
            if pre.val < head.val > head.next.val or pre.val > head.val < head.next.val:
                if first == -1:
                    first = i
                else:
                    ans[0] = min(ans[0], i - last)
                    ans[1] = i - first
                last = i

            pre = head
            head = head.next
            i += 1
        return ans if ans[1] != -1 else [-1, -1]


if __name__ == "__main__":
    head = ListNode(5, ListNode(3, ListNode(1, ListNode(2, ListNode(5, ListNode(1,ListNode(2)))))))
    print(Solution().nodesBetweenCriticalPoints(head))  # Output: [1, 3]
