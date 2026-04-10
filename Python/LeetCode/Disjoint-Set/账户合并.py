from typing import List
from collections import defaultdict

class UnionFind:
    def __init__(self,n:int):
        self._fa = list(range(n))
        self._size = [1] * n
        self.cc = n
    
    def find(self,x:int)->int:
        fa = self._fa
        if fa[x] != x:
            fa[x] = self.find(fa[x])
        return fa[x]
    
    def union(self,x:int,y:int)->bool:
        x,y = self.find(x),self.find(y)
        if x==y:
            return False
        self._fa[x] = y
        self._size[y] += self._size[x]
        self.cc -= 1
        return True

class Solution:
    def accountsMerge(self, accounts: List[List[str]]) -> List[List[str]]:
        #建立邮箱到index的映射
        emailToIndex = dict()
        #建立邮箱到name的映射
        emailToName = dict()

        #遍历建立邮箱映射
        for account in accounts:
            name = account[0]
            for email in account[1:]:
                if email not in emailToIndex:
                    emailToIndex[email] = len(emailToIndex)
                    emailToName[email] = name
        
        #合并同一账号的邮箱
        uf = UnionFind(len(emailToIndex))
        for account in accounts:
            firstIndex = emailToIndex[account[1]]
            for email in account[2:]:
                uf.union(firstIndex,emailToIndex[email])

        #根据根节点分组邮箱
        indexToEmail = defaultdict(list)
        for email,index in emailToIndex.items():
            index = uf.find(index)
            indexToEmail[index].append(email)

        #梳理结果格式
        res = list()
        for emails in indexToEmail.values():
            name = emailToName[emails[0]]
            res.append([name]+sorted(emails))
        return res
    
if __name__ == "__main__":
    solution = Solution()
    accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
    print(solution.accountsMerge(accounts))  # 输出 [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'], ["Mary", "mary@mail.com"]]

