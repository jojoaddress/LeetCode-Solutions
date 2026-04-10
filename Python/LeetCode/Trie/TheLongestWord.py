from typing import List


class Node:
    __slots__ = "son", "end"

    def __init__(self):
        self.son = {}
        self.end = False


class Solution:
    def longestWord(self, words: List[str]) -> str:
        words.sort(key=len)
        self.root = Node()
        self.root.end = True
        res = ""
        for word in words:
            jud = True
            cur = self.root
            for c in word:
                if c not in cur.son:
                    cur.son[c] = Node()
                jud = jud and cur.end
                cur = cur.son[c]
            cur.end = True

            if jud and len(word) >= len(res):
                if len(word) == len(res):
                    res = min(res, word)
                else:
                    res = word
        return res
    
    def longestWord2(self, words: List[str]) -> str:
        words.sort(key=lambda x: (-len(x), x),reverse=True)
        longest = ""
        candidates = {""}
        for word in words:
            if word[:-1] in candidates:
                candidates.add(word)
                longest = word
        return longest

if __name__ == "__main__":
    solution = Solution()
    words = [
        "yo",
        "ew",
        "fc",
        "zrc",
        "yodn",
        "fcm",
        "qm",
        "qmo",
        "fcmz",
        "z",
        "ewq",
        "yod",
        "ewqz",
        "y",
    ]
    print(solution.longestWord2(words))  # 输出 "yodn"
