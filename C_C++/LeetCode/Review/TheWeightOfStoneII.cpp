#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
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
    int lastStoneWeightII(vector<int> &stones)
    {
        int n = stones.size();
        int sum = 0;
        for (auto &stone : stones)
            sum += stone;

        int target = sum / 2;
        vector<int> dp(target + 1, 0);
        for (int i = 0; i < n; i++)
        {
            for (int j = target; j >= stones[i]; j--)
            {
                dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
            }
        }
        int stoneMax = 2 * (*max_element(dp.begin(), dp.end()));
        return sum - stoneMax;
    }
};

int main()
{
    Solution sol;
    vector<int> stones = {2, 7, 4, 1, 8, 1};
    int result = sol.lastStoneWeightII(stones);
    cout << result << endl; // Output: 1
    return 0;
}