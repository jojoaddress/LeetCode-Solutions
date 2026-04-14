from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def numComponents(self, head: Optional[ListNode], nums: List[int]) -> int:
        cnt = set(nums)
        res = 0
        while head:
            if head.val in cnt:
                res += 1
                while head and head.val in cnt:
                    head = head.next
            else:
                head = head.next
        return res


if __name__ == "__main__":
    head = ListNode(0)
    head.next = ListNode(1)
    head.next.next = ListNode(2)
    head.next.next.next = ListNode(3)
    print(Solution().numComponents(head, [0, 1, 3]))
