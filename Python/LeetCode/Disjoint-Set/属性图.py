from typing import List


class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        fa = list(range(n))
        cc = n

        sets = [set(p) for p in properties]

        def find(x: int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]

        def union(x: int, y: int) -> bool:
            x, y = find(x), find(y)
            if x == y:
                return False
            fa[x] = y
            return True
        
        for i in range(n):
            for j in range(i + 1, n):
                if len(sets[i] & sets[j]) >= k:
                    if union(i, j):
                        cc -= 1
        return cc


if __name__ == "__main__":
    print(
        Solution().numberOfComponents(
            [[1, 2], [1, 1], [3, 4], [4, 5], [5, 6], [7, 7]], 1
        )
    )
