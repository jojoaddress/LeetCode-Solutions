from typing import List
from typing import Optional
from collections import defaultdict
import math

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def insertGreatestCommonDivisors(self, head: Optional[ListNode]) -> Optional[ListNode]:
        cur = head
        while cur.next:
            right = cur.next
            temp = math.gcd(cur.val,right.val)
            cur.next = ListNode(temp,right)
            cur = right
        return head
    
if __name__ == "__main__":
    head = ListNode(18, ListNode(6, ListNode(10, ListNode(3))))
    nums = [18,6,10,3]
    res = Solution().insertGreatestCommonDivisors(head)
    while res:
        print(res.val)
        res = res.next
            