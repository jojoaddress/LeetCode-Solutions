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
    def isSubPath(self, head: Optional[ListNode], root: Optional[TreeNode]) -> bool:
        def dfs(s:Optional[ListNode],h:Optional[TreeNode]):
            if not s:
                return True
            if not h:
                return False
            return s.val == h.val and (dfs(s.next,h.left) or dfs(s.next,h.right)) or s is head and (dfs(head,h.left) or dfs(head,h.right))
        return dfs(head,root)