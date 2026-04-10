from typing import List


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class Solution:
    def __init__(self):
        self.root = Node()

    def insert(self, word: str) -> None:
        cur = self.root
        for c in word:
            if c not in cur.son:
                cur.son[c] = Node()
            cur = cur.son[c]
        cur.end = True

    def find(self, word: str) -> str:
        t = ""
        cur = self.root
        for c in word:
            if c not in cur.son or cur.end == True:
                if cur.end == False:
                    t = ""
                break
            else:
                t += c
                cur = cur.son[c]

        return word if t=="" else t

    def replaceWords(self, dictionary: List[str], sentence: str) -> str:
        res = []
        for dic in dictionary:
            self.insert(dic)
        
        words = sentence.split()
        for word in words:
            res.append(self.find(word))
        return " ".join(res)

if __name__ == '__main__':
    solution = Solution()
    dictionary = ["a", "b", "c"]
    sentence = "aadsfasf absbs bbab cadsfafs"
    print(solution.replaceWords(dictionary, sentence))  # 输出 "the cat was rat by the bat"