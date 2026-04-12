#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int change(int amount, vector<int> &coins)
    {
        int n = coins.size();
        vector<int> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j <= amount; j++)
            {
                if (j >= coins[i])
                    dp[j] += dp[j - coins[i]];
            }
        }
        return dp[amount];
    }
};

int main()
{
    Solution solution;
    vector<int> coins = {1, 2, 5};
    int amount = 5;
    int result = solution.change(amount, coins);
    cout << result << endl;
    return 0;
}