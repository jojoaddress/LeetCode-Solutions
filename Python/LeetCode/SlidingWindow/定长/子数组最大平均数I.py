from typing import List

#nums = [−2,0,3,−5,2,−1]
#d = [0,−2,−2,1,−4,−2,−3]
# 求0-3 用s[4]-s[0]
# 即k=4 R-L=k
class Solution:
    def findMaxAverage(self, nums: List[int], k: int) -> float:
        res = float('-inf')
        s = [0] * (len(nums)+1)
        for i,x in enumerate(nums):
            s[i+1] = s[i] + x
            if i+1 >= k:
                res = max(res,s[i+1]-s[i+1-k])
        return res/k
        

    def findMaxAverage2(self, nums: List[int], k: int) -> float:
        res = float('-inf')
        tmp = 0
        for i,num in enumerate(nums):
            left = i-k+1
            tmp += num
            if left<0:
                continue
            res = max(res,tmp)
            tmp -= nums[left]
        return res/k

if __name__ == "__main__":
    print(Solution().findMaxAverage([1,12,-5,-6,50,3], 4))
