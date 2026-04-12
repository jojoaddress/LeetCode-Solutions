// dp[i][j]表示0~i个元素是否能任选其中的元素，使他们的和等于j
// nums[i]<j,可选可不选，所以dp[i][j]=dp[i-1][j]|dp[i][j-nums[i]]
// dp[i][0]=true,dp[0][nums[0]] = true

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool canPartition(vector<int> &nums)
    {
        int target = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            target += nums[i];
        }
        if (target % 2 != 0)
            return false;
        if (nums.size() == 1)
        {
            return false;
        }
        target /= 2;
        sort(nums.begin(), nums.end());
        vector<vector<bool>> dp(nums.size(), vector<bool>(target + 1, false));
        dp[0][nums[0]] = true;
        for (int i = 0; i < nums.size(); i++)
        {
            dp[i][0] = true;
        }
        for (int i = 1; i < nums.size(); i++)
        {
            int num = nums[i];
            for (int j = 1; j <= target; j++)
            {
                if (num > j)
                {
                    dp[i][j] = dp[i - 1][j];
                }
                else
                {
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                }
            }
        }
        return dp[nums.size() - 1][target];
    }
};

int main()
{
    auto s = new Solution();
    vector<int> nums = {1, 2, 3, 4};
    cout << s->canPartition(nums);
    return 0;
}