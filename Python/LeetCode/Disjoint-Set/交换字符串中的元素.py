from typing import List


class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self.cc = n

    def find(self, x: int) -> int:
        fa = self._fa
        if fa[x] != x:
            fa[x] = self.find(fa[x])
        return fa[x]

    def union(self, x: int, y: int) -> bool:
        x, y = self.find(x), self.find(y)
        if x == y:
            return False
        self._fa[x] = y
        self.cc -= 1
        return True

    def getComponent(self)-> dict[int, list[int]]:
        comps = {}
        for i in range(len(self._fa)):
            root = self.find(i)
            if root not in comps:
                comps[root] = []
            comps[root].append(i)
        return comps


class Solution:
    def smallestStringWithSwaps(self, s: str, pairs: List[List[int]]) -> str:
        uf = UnionFind(len(s))
        for pair in pairs:
            uf.union(pair[0], pair[1])
        component = uf.getComponent()

        res = list(s)
        for comp in component.values():
            chars = [res[i] for i in comp]
            chars.sort()
            for i, c in zip(comp, chars):
                res[i] = c
        return ''.join(res)

if __name__ == "__main__":
    print(Solution().smallestStringWithSwaps("dcab", [[0,3],[1,2]]))
