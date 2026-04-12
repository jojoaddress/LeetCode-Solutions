/* 2024.1.22
 *
 * 完全平方数
 * 给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
 * 完全平方数 是一个整数，其值等于另一个整数的平方；
 * 换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
 * 
 * dp[i] 表示最少需要多少个数的平方来表示整数 i
 * 这些数必然落在区间 [1,n]。我们可以枚举这些数，假设当前枚举到 j，那么我们还需要取若干数的平方，构成 i−j^2
 * 此时我们发现该子问题和原问题类似，只是规模变小了。这符合了动态规划的要求，于是我们可以写出状态转移方程 dp[i] = 1 + min dp[i-j^2]
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int numSquares(int n)
    {
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++)
        {
            int minTemp = INT_MAX;
            for (int j = 1; j * j <= i; j++)
            {
                minTemp = min(minTemp,dp[i-j*j]);
            }
            dp[i] = 1 + minTemp;
        }
        return dp[n];
    }
};

int main()
{
    Solution *s = new Solution();
    cout<<s->numSquares(12);
    return 0;
}
