from typing import List
from typing import Optional
from collections import defaultdict
from math import inf

class Employee:
    def __init__(self, id: int, importance: int, subordinates: List[int]):
        self.id = id
        self.importance = importance
        self.subordinates = subordinates

class Solution:
    def getImportance(self, employees: List['Employee'], id: int) -> int:
        emp = {e.id: e for e in employees}
        def dfs(id: int) -> int:
            res = 0
            for c in emp[id].subordinates:
                res +=dfs(c)
            return res+emp[id].importance
        
        return dfs(id)
    
if __name__ == "__main__":
    employees = [
        Employee(1, 5, [2, 3]),
        Employee(2, 3, []),
        Employee(3, 3, [])
    ]
    solution = Solution()
    print(solution.getImportance(employees, 1))
