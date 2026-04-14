from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


class Solution:
    def splitListToParts(
        self, head: Optional[ListNode], k: int
    ) -> List[Optional[ListNode]]:
        cnt = head
        length = 0
        while cnt:
            length += 1
            cnt = cnt.next

        part_length = length // k
        reminder = length % k

        res = []
        cur_part_node = head
        for i in range(k):
            cur_part_head = cur_part_node
            cur_part_length = part_length

            if reminder:
                reminder -= 1
                cur_part_length += 1

            for j in range(cur_part_length - 1):
                if cur_part_node:
                    cur_part_node = cur_part_node.next

            if cur_part_node:
                tmp = cur_part_node.next
                cur_part_node.next = None
                cur_part_node = tmp
            res.append(cur_part_head)
        return res


if __name__ == "__main__":
    head = ListNode(1, ListNode(2, ListNode(3)))
    k = 5
    res = Solution().splitListToParts(head, k)
    for part in res:
        part_values = []
        while part:
            part_values.append(part.val)
            part = part.next
        print(part_values)  # Output: [[1], [2], [3], [], []]
