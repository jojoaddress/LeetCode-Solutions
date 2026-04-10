from typing import List


class UnionFind:
    def __init__(self, n: int):
        self.parent = list(range(n))

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        x, y = self.find(x), self.find(y)
        if x == y:
            return False
        self.parent[x] = y
        return True

    def isConnect(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)


class Solution:
    def pathExistenceQueries(
        self, n: int, nums: List[int], maxDiff: int, queries: List[List[int]]
    ) -> List[bool]:
        uf = UnionFind(n)
        for i in range(n-1):
                if nums[i+1] - nums[i] <= maxDiff:
                    uf.union(i, i+1)
        res = list()
        for q in queries:
            res.append(uf.isConnect(q[0], q[1]))
        return res


if __name__ == "__main__":
    print(
        Solution().pathExistenceQueries(
            4, [2, 5, 6, 8], 2, [[0, 1], [0, 2], [1, 3], [2, 3]]
        )
    )
