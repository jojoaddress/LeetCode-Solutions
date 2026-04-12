/* 2023.12.26
 *
 * 爬楼梯
 * 动态规划核心思想：记住求过的解来节省时间。
 * s[n]=s[n-1]+s[n-2]
 * s1=1 s2=2
 * s3=s1+s2=3
 * s4=s3+s2=5
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int climbStairs(int n)
    {

        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        if (n <= 2)
        {
            return n;
        }
        for (int i = 3; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};

class Solution_plus
{
public:
    int climbStairs(int n)
    {
        if (n <= 2)
        {
            return n;
        }
        int s1 = 1, s2 = 2;
        int temp;
        for (int i = 3; i <= n; i++)
        {
            temp = s1;
            s1 = s2;
            s2 = temp + s1;
        }
        return s2;
    }
};

int main()
{
    Solution_plus *s = new Solution_plus();
    s->climbStairs(3);
    return 0;
}