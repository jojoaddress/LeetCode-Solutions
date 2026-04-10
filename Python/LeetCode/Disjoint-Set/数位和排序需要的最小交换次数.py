from typing import List

class UnionFind:
    def __init__(self,n:int):
        self._fa = list(range(n))
        self._size = [1] * n
        self.cc = n
    
    def find(self,x:int)->int:
        fa = self._fa
        if fa[x]!= x:
            fa[x] = self.find(fa[x])
        return fa[x]

    def union(self,x:int,y:int)->bool:
        x,y = self.find(x),self.find(y)
        if x==y:
            return False
        self._fa[x] = y
        self._size[y] += self._size[x]
        self.cc -= 1
        return True
    
    def getComponentSize(self):
        sizes = []
        for i in range(len(self._fa)):
            if self.find(i) == i:
                sizes.append(self._size[i])
        return sizes

class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        numSort = sorted((sum(map(int,str(x))), x, i) for i, x in enumerate(nums))
        n = len(numSort)
        uf = UnionFind(n)
        for i, x in enumerate(numSort):
            uf.union(x[2], i)
        # ∑(k-1) for each connected component
        sizes = uf.getComponentSize()
        res = 0
        for s in sizes:
            res += s - 1
        return res
        # 也等于 n - number of connected components
        # return n - uf.cc
    
    
if __name__ == "__main__":
    print(Solution().minSwaps([22,14,33,7]))
            