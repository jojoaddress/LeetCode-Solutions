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
    def findFrequentTreeSum(self, root: Optional[TreeNode]) -> List[int]:
        cnt = defaultdict(int)
        maxNum=0
        def dfs(root:Optional[TreeNode])->int:
            nonlocal maxNum
            if root is None:
                return 0
            left = dfs(root.left)
            right = dfs(root.right)
            num = root.val + left + right
            cnt[num]+=1
            maxNum = max(maxNum,cnt[num])
            return num
        dfs(root)
        return [item for item,c in cnt.items() if c == maxNum]

if __name__ == "__main__":
    solution = Solution()
    root = TreeNode(5)
    root.left = TreeNode(2)
    root.right = TreeNode(-3)

    print(solution.findFrequentTreeSum(root))
        
            