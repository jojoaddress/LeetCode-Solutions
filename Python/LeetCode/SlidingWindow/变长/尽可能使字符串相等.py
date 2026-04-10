from typing import List
from collections import defaultdict

class Solution:
    def equalSubstring(self, s: str, t: str, maxCost: int) -> int:
        currentCost = 0
        maxLen = 0
        left = 0
        for i,(c1,c2) in enumerate(zip(s,t)):
            currentCost += abs(ord(c1) - ord(c2))
            while currentCost > maxCost:
                currentCost -= abs(ord(s[left]) - ord(t[left]))
                left+=1
            maxLen = max(maxLen,i-left+1)
        return maxLen

if __name__ == "__main__":
    print(Solution().equalSubstring("abcd","bcdf",3))
