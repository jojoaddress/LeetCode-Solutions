#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
    int minCostClimbingStairs(vector<int> &cost)
    {
        vector<int> dp(cost.size() + 1, 0);
        dp[0] = cost[0];
        dp[1] = cost[1];
        for (int i = 2; i <= cost.size(); i++)
        {
            dp[i] = min(dp[i - 1], dp[i - 2]);
            if (i != cost.size())
            {
                dp[i] += cost[i];
            }
        }
        return dp[cost.size()];
    }
};

int main()
{
    auto s = new Solution;
    vector<int> cost = {10, 15, 20};
    cout << s->minCostClimbingStairs(cost);
}