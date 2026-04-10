from typing import List
from collections import defaultdict
from functools import cache

class Trie:
    def __init__(self):
        self.son = defaultdict(Trie)
        self.end = ""
    
    def insert(self, word:str):
        cur = self
        for c in word:
            cur = cur.son[c]
        cur.end = word

class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> bool:
        max_len = max(map(len,wordDict))
        words = set(wordDict)

        @cache
        def dfs(i:int)->bool:
            if i == 0:
                return True
            for j in range(i-1,max(i-max_len-1,-1),-1):
                if s[j:i] in words and dfs(j):
                    return True
            return False
        
        return dfs(len(s))
    
if __name__ == "__main__":
    solution = Solution()
    s = "leetcode"
    wordDict = ["leet", "code"]
    print(solution.wordBreak(s, wordDict))  # 输出 True
