#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// y为前n-2的和，x为异常数字
// 2*y+x=sum
// y=(sum-x)/2
class Solution
{
public:
    int getLargestOutlier(vector<int> &nums)
    {
        int n = nums.size();
        unordered_map<int, int> cnt;
        int res = INT_MIN;
        int sum = 0;
        for (auto n : nums)
        {
            sum += n;
            cnt[n]++;
        }

        for (int i = 0; i < n; i++)
        {
            cnt[nums[i]]--;
            if ((sum - nums[i]) % 2 == 0 && cnt[(sum - nums[i]) / 2] > 0)
            {
                res = max(res, nums[i]);
            }
            cnt[nums[i]]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {6,-31,50,-35,41,37,-42,13};
    int res = sol.getLargestOutlier(nums);
    cout << res << endl; // Output: 6
    return 0;
}