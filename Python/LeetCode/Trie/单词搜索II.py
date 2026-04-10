from typing import List
from collections import defaultdict


class Trie:
    def __init__(self):
        self.son = defaultdict(Trie)
        self.word = ""

    def insert(self, word: str) -> None:
        cur = self
        for c in word:
            cur = cur.son[c]
        cur.word = word


class Solution:
    def findWords(self, board: List[List[str]], words: List[str]) -> List[str]:
        root = Trie()
        res = set()
        for word in words:
            root.insert(word)

        def dfs(cur: Trie, i1: int, j1: int):
            ch = board[i1][j1]
            if ch not in cur.son:
                return
            cur = cur.son[ch]
            if cur.word != "":
                res.add(cur.word)

            board[i1][j1] = "#"
            for i2, j2 in [(i1 + 1, j1), (i1, j1 + 1), (i1 - 1, j1), (i1, j1 - 1)]:
                if 0 <= i2 < m and 0 <= j2 < n:
                    dfs(cur, i2, j2)
            board[i1][j1] = ch

        m, n = len(board), len(board[0])
        for i in range(m):
            for j in range(n):
                dfs(root, i, j)
        return list(res)


if __name__ == "__main__":
    solution = Solution()
    board = [
        ["o", "a", "a", "n"],
        ["e", "t", "a", "e"],
        ["i", "h", "k", "r"],
        ["i", "f", "l", "v"],
    ]
    words = ["oath", "pea", "eat", "rain"]
    print(solution.findWords(board, words))  # 输出 ["eat","oath"]
