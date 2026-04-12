#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= amount; j++)
            {
                if (j >= coins[i] && dp[j - coins[i]] != INT_MAX)
                    dp[j] = min(dp[j], dp[j - coins[i]] + 1);
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }

    int coinChange2(vector<int> &coins, int amount)
    {
        int n = coins.size();
        vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INT_MAX));
        for (int i = 0; i <= n; i++)
            dp[i][0] = 0;

        for (int i = 1; i <= n;i++)
        {
            for (int j = 0; j <= amount;j++)
            {
                dp[i][j] = dp[i - 1][j];
                if(j>=coins[i-1]&&dp[i][j-coins[i-1]]!=INT_MAX)
                    dp[i][j] = min(dp[i][j], dp[i][j - coins[i - 1]] + 1);
            }
        }
        return dp[n][amount] == INT_MAX ? -1 : dp[n][amount];
    }
};

int main()
{
    Solution solution;
    vector<int> coins = {1, 2, 5};
    int amount = 11;
    int result = solution.coinChange(coins, amount);
    cout << "Minimum coins required: " << result << endl;
    return 0;
}