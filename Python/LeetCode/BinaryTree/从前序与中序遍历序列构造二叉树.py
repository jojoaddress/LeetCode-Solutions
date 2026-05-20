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
    def buildTree(self, preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
        if not preorder:
            return None
        leftsize = inorder.index(preorder[0])
        left = self.buildTree(preorder[1:leftsize+1],inorder[:leftsize])
        right = self.buildTree(preorder[leftsize+1:],inorder[leftsize+1:])
        return TreeNode(preorder[0],left,right)