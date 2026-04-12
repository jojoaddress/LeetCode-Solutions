#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxProfit_1(vector<int> &prices)
    {
        int n = prices.size();
        auto dp = vector<vector<int>>(n, vector<int>(2));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        for (int i = 1; i < n; i++)
        {
            dp[i][0] = max(dp[i - 1][0], -prices[i]);
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
        }
        return dp[n - 1][1];
    }

    int maxProfit(vector<int> &prices)
    {
        int ans = 0;
        int minPrice = prices[0];
        for (auto p : prices)
        {
            ans = max(ans, p - minPrice);
            minPrice = min(p, minPrice);
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> prices = {7, 1, 5, 3, 6, 4};
    cout << sol.maxProfit(prices) << endl;
    return 0;
}
