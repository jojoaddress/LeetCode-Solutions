
""" 
定长滑窗套路
窗口右端点在 i 时,由于窗口长度为 k,所以窗口左端点为 i-k+1。

我总结成三步：入-更新-出。

入：下标为 i 的元素进入窗口,更新相关统计量。如果窗口左端点 i-k+1<0,则尚未形成第一个窗口,重复第一步。
更新：更新答案。一般是更新最大值/最小值。
出：下标为 i-k+1 的元素离开窗口,更新相关统计量,为下一个循环做准备。 

对于窗口（闭区间）[L,R] 来说,[L,R] 里面的元素个数为 R-L+1。比如 [2,5] 里面有 2,3,4,5 一共 5-2+1=4 个数。
如果窗口大小为 k,
R-L+1=k
L=R-k+1。所以右端点为 R 的时候,左端点为 R-k+1。

"""

class Solution:
    def maxVowels(self, s: str, k: int) -> int:
        res = temp = 0
        for i, c in enumerate(s):
            # 第一步：入      
            if s[i] in "aeiou":
                temp += 1
            left = i - k + 1
            if left < 0:
                continue
            # 第二步：更新
            res = max(res, temp)
            # 第三步：出
            if s[left] in "aeiou":
                temp -= 1
        return res

if __name__ == "__main__":
    print(Solution().maxVowels("abciiidef", 3))