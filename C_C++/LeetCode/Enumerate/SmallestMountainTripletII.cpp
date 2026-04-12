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
    int minimumSum(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> right(n + 1, INT_MAX);
        for (int i = n - 2; i > 0; i--)
            right[i] = min(right[i + 1], nums[i + 1]);

        vector<int> left(n + 1, INT_MAX);
        int ans = INT_MAX;
        for (int i = 1; i < n; i++)
        {
            left[i] = min(left[i - 1], nums[i - 1]);
            if (nums[i] > left[i] && nums[i] > right[i])
            {
                ans = min(ans, nums[i] + left[i] + right[i]);
            }
        }
        return ans == INT_MAX ? -1 : ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {5, 4, 8, 7, 10, 2};
    cout << sol.minimumSum(nums) << endl; // Output: 10
    return 0;
}