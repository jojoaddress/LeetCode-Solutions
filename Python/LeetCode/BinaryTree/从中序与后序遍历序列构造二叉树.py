from typing import List
from typing import Optional
from collections import defaultdict
from collections import deque


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def buildTree(self, inorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if not postorder:
            return None
        m = len(postorder)
        leftsize = inorder.index(postorder[m-1])
        left = self.buildTree(inorder[:leftsize],postorder[:leftsize])
        right = self.buildTree(inorder[leftsize+1:],postorder[leftsize:m-1])
        return TreeNode(postorder[m-1],left,right)