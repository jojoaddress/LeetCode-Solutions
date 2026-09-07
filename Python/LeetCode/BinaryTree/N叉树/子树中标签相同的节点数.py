from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from collections import deque
from math import inf


class Solution:
    def countSubTrees(self, n: int, edges: List[List[int]], labels: str) -> List[int]:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        res = [0] * n

        def dfs(u: int, parent: int) -> List[int]:
            count = [0] * 26
            count[ord(labels[u]) - ord("a")] += 1

            for v in g[u]:
                if v == parent:
                    continue  # 避免回到父节点
                child_count = dfs(v, u)
                # 累加子树的计数
                for i in range(26):
                    count[i] += child_count[i]

            # 当前节点的答案就是其标签字母的计数
            res[u] = count[ord(labels[u]) - ord("a")]
            return count

        dfs(0, -1)
        return res


if __name__ == "__main__":
    n = 5
    edges = [[0, 1], [0, 2], [1, 3], [0, 4]]
    labels = "aabab"
    print(Solution().countSubTrees(n, edges, labels))
