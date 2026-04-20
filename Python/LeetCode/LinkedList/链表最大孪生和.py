from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def reverse(self, head: Optional[ListNode]) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre

    def pairSum2(self, head: Optional[ListNode]) -> int:
        left = right = dummy = ListNode(next=head)
        while right and right.next:
            left = left.next
            right = right.next.next

        new_head = self.reverse(left.next)
        left.next = None
        res = 0
        while new_head and head:
            res = max(res, new_head.val + head.val)
            new_head = new_head.next
            head = head.next
        return res

    def pairSum(self, head: Optional[ListNode]) -> int:
        nums = []
        while head:
            nums.append(head.val)
            head = head.next
        numslen = len(nums)
        res = 0
        for i in range(numslen // 2):
            res = max(res, nums[i] + nums[numslen - 1 - i])
        return res


if __name__ == "__main__":
    head = ListNode(5)
    head.next = ListNode(4)

    n = 3

    print(Solution().pairSum(head))
