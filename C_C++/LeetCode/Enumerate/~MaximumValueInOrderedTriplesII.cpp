#include <algorithm>
#include <bitset>
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
    long long maximumTripletValue(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> right(n + 1);
        vector<int> left(n + 1);
        for (int i = n - 2; i > 0; i--)
        {
            right[i] = max(right[i + 1], nums[i + 1]);
        }

        long long ans = 0;
        for (int i = 1; i < n; i++)
        {
            left[i] = max(left[i - 1], nums[i - 1]);
            ans = max(ans, 1LL * (left[i] - nums[i]) * right[i]);
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1,10,3,4,19};
    cout << sol.maximumTripletValue(nums) << endl; // Output: 77
    return 0;
}