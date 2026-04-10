
from typing import List

class Node:
    __slots__ = "son", "end"
    def __init__(self):
        self.son = {}
        self.end = False

class WordDictionary:
    
    def __init__(self):
        self.root = Node()

    def addWord(self, word: str) -> None:
        cur = self.root
        for w in word:
            if w not in cur.son:
                cur.son[w] = Node()
            cur = cur.son[w]
        cur.end = True

    def dfs(self,cur:Node,word:str,idx:int) ->bool:
        if idx == len(word):
            return cur.end
        ch = word[idx]
        if ch == '.':
            for child in cur.son.values():
                if self.dfs(child,word,idx+1):
                    return True
            return False
        else:
            if ch not in cur.son:
                return False
            return self.dfs(cur.son[ch],word,idx+1)
    def search(self, word: str) -> bool:
        return self.dfs(self.root,word,0)
    

if __name__ == "__main__":
    wordDictionary = WordDictionary()
    wordDictionary.addWord("bad")
    wordDictionary.addWord("dad")
    wordDictionary.addWord("mad")
    print(wordDictionary.search("pad"))  # 返回 False
    print(wordDictionary.search("bad"))  # 返回 True
    print(wordDictionary.search(".ad"))  # 返回 True
    print(wordDictionary.search("b.."))  # 返回 True