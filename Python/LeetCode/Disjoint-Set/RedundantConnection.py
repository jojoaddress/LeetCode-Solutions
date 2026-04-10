from typing import List
from collections import defaultdict
from functools import cache


class Solution:
    def findRedundantConnection(self, edges: List[List[int]]) -> List[int]:
        n = len(edges)
        fa = list(range(n + 1))

        def find(x: int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]

        def merge(x: int, y: int) -> None:
            fa[find(x)] = find(y)

        for node1, node2 in edges:
            if find(node1) != find(node2):
                merge(node1, node2)
            else:
                return [node1, node2]
        return []


if __name__ == "__main__":
    solution = Solution()
    edges = [[1, 2], [1, 3], [2, 3]]
    print(solution.findRedundantConnection(edges))  # 输出 [2,3]
