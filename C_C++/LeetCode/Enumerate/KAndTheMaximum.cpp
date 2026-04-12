#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

//nums[i]+nums[j]=k,nums[i]=k-nums[j]
class Solution
{
public:
    int maxOperations(vector<int> &nums, int k)
    {
        int n = nums.size();
        int res = 0;
        unordered_map<int, int> cnt;
        for (int i = 0; i < n; i++)
        {
            auto it = cnt.find(k - nums[i]);
            if (it != cnt.end()&&it->second>0)
            {
                res++;
                cnt[k - nums[i]]--;
                continue;
            }
            cnt[nums[i]]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1,2,3,4};
    int k = 5;
    cout << sol.maxOperations(nums,k) << endl;
    return 0;
}