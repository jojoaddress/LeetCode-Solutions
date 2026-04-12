/* 2024.1.22
 *
 * 零钱兑换
 *
 * 给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
 * 计算并返回可以凑成总金额所需的 最少的硬币个数 。如果没有任何一种硬币组合能组成总金额，返回 -1 。
 * 你可以认为每种硬币的数量是无限的。
 *
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int> dp(amount + 1, amount + 1);
        int len = coins.size();
        dp[0] = 0;
        for (int i = 1; i <= amount; i++)
        {
            int minTemp = INT_MAX;
            for (int j = 0; j < len; j++)
            {
                if (i >= coins[j])
                {
                    minTemp = min(minTemp, dp[i - coins[j]]);
                }
            }
            if(minTemp == INT_MAX)
            {
                continue;
            }
            dp[i] = minTemp + 1;
        }
        return dp[amount] > amount ? -1 : dp[amount];
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> conis = {1};
    int amount = 1;
    cout << s->coinChange(conis, amount);
    return 0;
}
