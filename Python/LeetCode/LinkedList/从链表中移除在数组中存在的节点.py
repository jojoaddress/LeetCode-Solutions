from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def modifiedList(
        self, nums: List[int], head: Optional[ListNode]
    ) -> Optional[ListNode]:
        cur = dummy = ListNode(next=head)
        num_set = set(nums)
        while cur.next:
            if cur.next.val in num_set:
                cur.next = cur.next.next
            else:
                cur = cur.next
        return dummy.next


if __name__ == "__main__":
    head = ListNode(1, ListNode(2, ListNode(3, ListNode(4, ListNode(5)))))
    nums = [1, 2, 3]
    res = Solution().modifiedList(nums, head)
    while res:
        print(res.val)
        res = res.next
