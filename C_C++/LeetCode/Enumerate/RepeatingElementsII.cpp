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
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        int n = nums.size();
        unordered_map<int, int> cnt;
        for (int i = 0; i < n; i++)
        {
            auto it = cnt.find(nums[i]);
            if(it!=cnt.end()&&abs(i-cnt[nums[i]])<=k)
            {
                return true;
            }
            cnt[nums[i]] = i;
        }
        return false;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 2, 3, 1};
    int k = 3;
    cout << (sol.containsNearbyDuplicate(nums, k) ? "true" : "false") << endl;
    return 0;
}