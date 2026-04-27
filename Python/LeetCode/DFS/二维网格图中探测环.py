from typing import List
from typing import Optional
from collections import defaultdict


class Solution1:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        vis = [[False] * n for _ in range(m)]

        dx = [0, 0, 1, -1]
        dy = [1, -1, 0, 0]

        def dfs(x, y, prex, prey) -> bool:
            if x >= m or x < 0 or y >= n or y < 0:
                return False
            if prex != -1 and grid[x][y] != grid[prex][prey]:
                return False
            if vis[x][y]:
                return True
            vis[x][y] = True
            for i in range(4):
                if x + dx[i] == prex and y + dy[i] == prey:
                    continue
                if dfs(x + dx[i], y + dy[i], x, y):
                    return True
            return False

        for i in range(m):
            for j in range(n):
                if not vis[i][j] and dfs(i, j, -1, -1):
                    return True
        return False


class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self._size = [1] * n
        self.cc = n

    def find(self, x: int) -> int:
        fa = self._fa
        if fa[x] != x:
            fa[x] = self.find(fa[x])
        return fa[x]

    def is_same(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)

    def merge(self, from_: int, to_: int) -> bool:
        x, y = self.find(from_), self.find(to_)
        if x == y:
            return False
        self._fa[x] = y
        self._size[y] += self._size[x]
        self.cc -= 1
        return True


class Solution:
    def containsCycle(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        union = UnionFind(n * m)

        for i in range(m):
            for j in range(n):
                idx = n * i + j
                if i + 1 < m and grid[i][j] == grid[i + 1][j]:
                    neighborIdx = n * (i + 1) + j
                    if union.is_same(idx, neighborIdx):
                        return True
                    union.merge(idx, neighborIdx)
                if j + 1 < n and grid[i][j] == grid[i][j + 1]:
                    neighborIdx = n * i + j + 1
                    if union.is_same(idx, neighborIdx):
                        return True
                    union.merge(idx, neighborIdx)
        return False

if __name__ == "__main__":
    grid = [
        ["a", "a", "a", "a"],
        ["a", "b", "b", "a"],
        ["a", "b", "b", "a"],
        ["a", "a", "a", "a"],
    ]
    print(Solution().containsCycle(grid))
