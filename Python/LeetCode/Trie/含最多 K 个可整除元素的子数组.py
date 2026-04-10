from typing import List


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class Solution:

    def countDistinct(self, nums: List[int], k: int, p: int) -> int:
        root = Node()
        self.res = 0

        def dfs(start: int, cur: Node, cnt: int) -> None:
            if start >= len(nums):
                return
            if nums[start] % p == 0:
                cnt += 1
            if cnt > k:
                return
            if nums[start] not in cur.son:
                cur.son[nums[start]] = Node()
                self.res += 1

            dfs(start + 1, cur.son[nums[start]], cnt)
        
        for start in range(len(nums)):
            dfs(start,root,0)
        
        return self.res
    
if __name__ == "__main__":
    s = Solution()
    print(s.countDistinct([2,3,3,2,2], 2, 2))  # 输出 11
    print(s.countDistinct([1,2,3,4], 4, 1))  # 输出 10

