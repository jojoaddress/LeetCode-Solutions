from typing import List
from typing import Optional
from collections import defaultdict
import math


class Node:
    def __init__(self, val=None, next=None):
        self.val = val
        self.next = next


class Solution:
    def insert(self, head: "Node", insertVal: int) -> "Node":
        insertNode = Node(val=insertVal)
        if head == None:
            insertNode.next = insertNode
            return insertNode
        if head.next == head:
            head.next = insertNode
            insertNode.next = head
            return head
        pre = head
        cur = pre.next
        while cur != head:
            if pre.val <= insertVal and cur.val >= insertVal:
                break
            if pre.val > cur.val:
                if insertVal > pre.val or insertVal < cur.val:
                    break
            pre = cur
            cur = pre.next
        pre.next = insertNode
        insertNode.next = cur
        return head


if __name__ == "__main__":
    head = Node(3, Node(3, Node(3, Node(0))))
    nums = [18, 6, 10, 3]
    res = Solution().insert(head, 0)
    while res:
        print(res.val)
        res = res.next
