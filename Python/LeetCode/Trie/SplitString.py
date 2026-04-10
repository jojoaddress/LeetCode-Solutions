from typing import List

class Solution:
    def partitionString(self, s: str) -> List[str]:
        res = []
        st = set()
        t = ""
        for c in s:
            t += c
            if t not in st:
                res.append(t)
                st.add(t)
                t = ""
        return res
    
    def partitionString2(self, s: str) -> List[str]:
        res = []
        cur = root = {}
        left = 0
        for i,c in enumerate(s):
            if c not in cur:
                cur[c] = {}
                res.append(s[left:i+1])
                left = i+1
                cur = root
            else:
                cur = cur[c]
        return res
#test
s = "abbccccd"
solution = Solution()
print(solution.partitionString(s))  # 输出 ["a","b","a","c","a","b","a"]
