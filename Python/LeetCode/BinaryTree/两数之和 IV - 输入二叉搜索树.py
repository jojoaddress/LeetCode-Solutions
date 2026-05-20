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
    def findTarget(self, root: Optional[TreeNode], k: int) -> bool:
        cnt = defaultdict(int)

        def dfs(root:Optional[TreeNode])->bool:
            if root is None:
                return False
            if cnt[k-root.val] >0:
                return True
            cnt[root.val]+=1
            return dfs(root.left) or dfs(root.right)
        
        return dfs(root)

if __name__ == "__main__":
    root1 = TreeNode(1)


    print(Solution().findTarget(root1,2))