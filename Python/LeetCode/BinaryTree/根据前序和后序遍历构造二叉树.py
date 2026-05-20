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
    def constructFromPrePost(self, preorder: List[int], postorder: List[int]) -> Optional[TreeNode]:
        if not preorder:
            return None
        if len(preorder)==1:
            return TreeNode(preorder[0])
        leftsize = postorder.index(preorder[1])+1
        left = self.constructFromPrePost(preorder[1:leftsize+1],postorder[:leftsize])
        right = self.constructFromPrePost(preorder[leftsize+1:],postorder[leftsize:-1])
        return TreeNode(preorder[-1],left,right)