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
    int numIdenticalPairs(vector<int> &nums)
    {
        int n = nums.size();
        int res = 0;
        unordered_map<int, int> cnt;
        for (int i = 0; i < n; i++)
        {
            auto it = cnt.find(nums[i]);
            if (it != cnt.end())
            {
                res=res+cnt[nums[i]];
            }
            cnt[nums[i]]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1,2,3,1,1,3};
    int res = sol.numIdenticalPairs(nums);
    cout << res << endl; // Output: 4
    return 0;
}