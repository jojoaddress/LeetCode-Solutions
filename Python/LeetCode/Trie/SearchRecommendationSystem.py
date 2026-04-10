from typing import List


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class Solution:
    def __init__(self):
        self.root = Node()

    def insert(self, products: List[str]) -> None:
        for p in products:
            cur = self.root
            for c in p:
                if c not in cur.son:
                    cur.son[c] = Node()
                cur = cur.son[c]
            cur.end = True

    def dfs(self, node: Node, path: list, result: list):
        if node.end:
            result.append("".join(path))  # 找到一个完整单词

        for ch, child in node.son.items():
            path.append(ch)  # 添加当前字符到路径
            self.dfs(child, path, result)  # 递归子节点
            path.pop()  # 回溯

    def find(self, word: str) -> List[str]:
        cur = self.root
        for w in word:
            if w not in cur.son:
                return []
            cur = cur.son[w]
        res = []
        self.dfs(cur, list(word), res)
        return res

    def suggestedProducts(
        self, products: List[str], searchWord: str
    ) -> List[List[str]]:
        res = []
        self.insert(products)
        word = ""
        for c in searchWord:
            word += c
            tmp = self.find(word)
            tmp.sort()
            res.append(tmp[:3])
        return res


if __name__ == "__main__":
    solution = Solution()
    products = ["mobile", "mouse", "moneypot", "monitor", "mousepad"]
    searchWord = "mouse"
    print(
        solution.suggestedProducts(products, searchWord)
    )  # 预期输出 [["mobile","moneypot","monitor"],["mobile","moneypot","monitor"],["mouse","mousepad"],["mouse","mousepad"],["mouse","mousepad"]]
