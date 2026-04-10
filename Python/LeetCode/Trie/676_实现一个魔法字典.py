from typing import List


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class MagicDictionary:

    def __init__(self):
        self.root = Node()

    def buildDict(self, dictionary: List[str]) -> None:
        for dic in dictionary:
            cur = self.root
            for c in dic:
                if c not in cur.son:
                    cur.son[c] = Node()
                cur = cur.son[c]
            cur.end = True

    def dfs(self, searchWord: str, cur: Node, idx: int,modified:bool) -> bool:
        if idx == len(searchWord):
            return cur.end and modified
        ch = searchWord[idx]
        if ch in cur.son:
            if self.dfs(searchWord, cur.son[ch], idx + 1,modified):
                return True
        if not modified:
            for c, child in cur.son.items():
                if c != ch:
                    if self.dfs(searchWord, child, idx + 1,True):
                        return True
        return False

    def search(self, searchWord: str) -> bool:
        return self.dfs(searchWord,self.root,0,False)


if __name__ == "__main__":
    magicDictionary = MagicDictionary()
    magicDictionary.buildDict(["hello", "hallo", "leetcode"])
    print(magicDictionary.search("hello"))  # 返回 True
    print(magicDictionary.search("hhllo"))  # 返回 True
    print(magicDictionary.search("hell"))  # 返回 False
    print(magicDictionary.search("leetcoded"))  # 返回 False
