from typing import List
from collections import defaultdict
""" 
排序后，选出的区间是连续的，
我们只需考虑最左边的区间 [x−k,x+k] 和最右边的区间 [y−k,y+k]，
如果这两个区间的交集不为空，那么选出的这些区间的交集就不为空。也就是说，要满足：
x+k>=y-k
y-x<=2k
 """
class Solution:
    def maximumBeauty(self, nums: List[int], k: int) -> int:
        nums.sort()
        maxLen = 0
        left = 0
        for i,num in enumerate(nums):
            while num-nums[left] > 2*k:
                left+=1
            maxLen = max(maxLen,i-left+1)
        return maxLen

if __name__ == "__main__":
    print(Solution().maximumBeauty([4,6,1,2], 2))