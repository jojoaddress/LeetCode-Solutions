from typing import List

class Solution:
    class UnionFin:
        def __init__(self,n:int):
            self._fa = list(range(n))

        def find(self,x:int)->int:
            fa = self._fa
            if fa[x]!=x:
                fa[x] = self.find(fa[x])
            return fa[x]
        
        def union(self,x:int,y:int)->None:
            self._fa[self.find(x)] = self.find(y)

    def equationsPossible(self, equations: List[str]) -> bool:
        uf = Solution.UnionFin(26)
        for equation in equations:
            if equation[1] == '=':
                x = ord(equation[0]) - ord('a')
                y = ord(equation[3]) - ord('a')
                uf.union(x,y)
        
        for equation in equations:
            if equation[1] == '!':
                x = ord(equation[0]) - ord('a')
                y = ord(equation[3]) - ord('a')
                if uf.find(x) == uf.find(y):
                    return False
        return True
    
if __name__ == "__main__":
    print(Solution().equationsPossible(["b==a","a==b"]))