from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

""" 
有趣的删除操作：
1.原4 -> 5 -> 1 -> 9
2.node.val = node.next.val后，变4 -> 1 -> 1 -> 9
3.node.next = node.next.next后，变4 -> 1    -> 9

这道题细思极恐：如何让自己在世界上消失，但又不死？ —— 将自己完全变成另一个人，再杀了那个人就行了。
"""
class Solution:
    def deleteNode(self, node):
        node.val = node.next.val
        node.next = node.next.next