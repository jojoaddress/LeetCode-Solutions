from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList(self, head: Optional[ListNode],end: Optional[ListNode]) -> Optional[ListNode]:
        pre = None
        cur = head
        while cur!=end:
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        return pre
    
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        cur = dummy = ListNode(next=head)
        pre = cur
        cnt = 0
        while cur:
            if cnt%k==0 and cnt!=0:
                nxt = cur.next
                tmpStart = pre.next
                tmpTail = self.reverseList(tmpStart,nxt)
                pre.next = tmpTail
                tmpStart.next = nxt
                pre = tmpStart
                cur = pre.next
            else:
                cur = cur.next
            cnt +=1
        return dummy.next
    
if __name__ == '__main__':
    head = ListNode(1)
    head.next = ListNode(2)
    head.next.next = ListNode(3)
    head.next.next.next = ListNode(4)
    head.next.next.next.next = ListNode(5)
    left = 2
    res = Solution().reverseKGroup(head,left)
    while res:
        print(res.val)
        res = res.next