from typing import List
from typing import Optional
from collections import defaultdict


class Solution:
    def hasValidPath(self, grid: List[List[int]]) -> bool:
        m, n = len(grid), len(grid[0])
        vis = [[False] * n for _ in range(m)]
        streets = (
            (),
            ((0, -1), (0, 1)),  # 站在街道 1，可以往左或者往右
            ((-1, 0), (1, 0)),  # 站在街道 2，可以往上或者往下
            ((0, -1), (1, 0)),  # 站在街道 3，可以往左或者往下
            ((0, 1), (1, 0)),  # 站在街道 4，可以往右或者往下
            ((0, -1), (-1, 0)),  # 站在街道 5，可以往左或者往上
            ((0, 1), (-1, 0)),  # 站在街道 6，可以往右或者往上
        )

        def dfs(x: int, y: int) -> bool:
            if x == m - 1 and y == n - 1:
                return True
            vis[x][y] = True
            for street in streets[grid[x][y]]:
                i = street[0] + x
                j = street[1] + y
                if (
                    not (0 <= i < m and 0 <= j < n)
                    or (-street[0], -street[1]) not in streets[grid[i][j]]
                    or vis[i][j]
                ):
                    continue
                if dfs(i, j):
                    return True
            vis[x][y] = False
            return False

        return dfs(0, 0)


if __name__ == "__main__":
    s = Solution()
    print(s.hasValidPath([[2, 4, 3], [6, 5, 2]]))
