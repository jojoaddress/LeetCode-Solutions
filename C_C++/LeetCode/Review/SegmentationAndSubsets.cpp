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

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        for(auto &num:nums)
            sum += num;
        if(sum%2!=0||sum==0)
            return false;
        int target = sum / 2;
        vector<bool> dp(target + 1, false);
        dp[0] = true;
        for (int i = 0; i < n;i++)
        {
            for (int j = target; j >= nums[i];j--)
            {
                dp[j] = dp[j] || dp[j - nums[i]];
            }
        }
        return dp[target];
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 5, 11, 5};
    bool result = sol.canPartition(nums);
    cout << (result ? "true" : "false") << endl; // Output: true
    return 0;   
}