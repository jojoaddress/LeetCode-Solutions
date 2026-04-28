from typing import List
from typing import Optional
from collections import defaultdict
from bisect import bisect_left
from itertools import accumulate

class Solution:
    def minOperations(self, grid: List[List[int]], x: int) -> int:
        nums = [x for row in grid for x in row]
        remainder = nums[0] % x
        for num in nums:
            if num%x!=remainder:
                return -1
        
        y = sorted([(num-remainder)//x for num in nums])
        n = len(y)
        median = y[n//2]
        ops = sum(abs(val-median) for val in y)
        return ops
    
if __name__ == "__main__":
    solution = Solution()
    print(solution.minOperations([[1,2,3],[4,5,6],[7,8,9]], 1)) # 20
    print(solution.minOperations([[1,10,100],[1000,10000,100000],[1000000,10000000,100000000]], 10)) # -1
        
