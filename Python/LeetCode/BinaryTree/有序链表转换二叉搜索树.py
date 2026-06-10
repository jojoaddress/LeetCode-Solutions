from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque

class ListNode:
     def __init__(self, val=0, next=None):
         self.val = val
         self.next = next

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def sortedListToBST(self, head: Optional[ListNode]) -> Optional[TreeNode]:
        if not head:
            return None
        cur= head
        res = []
        while cur:
            res.append(cur.val)
            cur = cur.next
        
        def dfs(res:List[int])-> Optional[TreeNode]:
            if not res:
                return None
            m = len(res)//2
            left = dfs(res[:m])
            right  = dfs(res[m+1:])
            return TreeNode(res[m],left,right)
        return dfs(res)