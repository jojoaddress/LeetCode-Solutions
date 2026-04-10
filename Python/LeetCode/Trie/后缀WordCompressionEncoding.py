from typing import List

class Node:
    __slots__ = 'son','end'
    def __init__(self):
        self.son = {}
        self.end = False

class Solution:
    def minimumLengthEncoding(self, words: List[str]) -> int:
        good = set(words)
        for word in words:
            for k in range(1,len(word)):
                good.discard(word[k:])
        return sum(len(word)+1 for word in good)

    def minimumLengthEncoding2(self, words: List[str]) -> int:
        words = list(set(words))
        root = Node()
        nodes = []
        for word in words:
            cur = root
            for w in reversed(word):
                if w not in cur.son:
                    cur.son[w] = Node()
                cur = cur.son[w]
            nodes.append(cur)
        ans = 0
        for n,w in zip(nodes,words):
            if len(n.son)==0 :
                ans += len(w)+1
        return ans



if __name__ == "__main__":
    s = Solution()
    print(s.minimumLengthEncoding2(["time", "me", "bell"]))  # 输出 10
    print(s.minimumLengthEncoding2(["t"]))  # 输出 2