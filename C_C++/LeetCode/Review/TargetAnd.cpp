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

// sum - 2*decrease = target, decrease = (sum - target)/2
class Solution
{
public:
    int findTargetSumWays(vector<int> &nums, int target)
    {
        int n = nums.size();
        int sum = 0;
        for (auto &num : nums)
            sum += num;

        if ((sum - target) % 2 != 0 || sum < target)
            return 0;
        int decrease = (sum - target) / 2;
        vector<int> dp(decrease + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = decrease; j >= nums[i]; j--)
            {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[decrease];
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 1, 1, 1, 1};
    int target = 3;
    int result = sol.findTargetSumWays(nums, target);
    cout << result << endl; // Output: 5
    return 0;
}