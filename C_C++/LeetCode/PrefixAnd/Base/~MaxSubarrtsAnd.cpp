#include <algorithm>
#include <iostream>
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
    // 动态规划
    int maxSubArray_(vector<int> &nums)
    {
        int n = nums.size();
        int ans = INT_MIN;
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++)
        {
            dp[i] = max(dp[i - 1] + nums[i - 1], nums[i - 1]);
            ans = max(dp[i], ans);
        }
        return ans;
    }
    // 前缀和，类似于最佳股票买卖时机
    int maxSubArray(vector<int> &nums)
    {
        int n = nums.size();
        int sMin = 0, ans = INT_MIN, s = 0;
        for (int i = 0; i < n; i++)
        {
            s += nums[i];
            ans = max(ans, s - sMin);
            sMin = min(sMin, s);
        }
        return ans;
    }

    //没有注意到区间连续性
    int maxSubArray__(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 1)
            return nums[0];
        int sMax = INT_MIN, sMin = 0, s = 0;
        for (int i = 0; i < n; i++)
        {
            s += nums[i];
            sMax = max(sMax, s);
            sMin = min(sMin, s);
        }
        return sMax - sMin;
    }
};

int main()
{
    vector<int> nums = {-2, -1};
    auto s = new Solution;
    cout << s->maxSubArray(nums);
    return 0;
}