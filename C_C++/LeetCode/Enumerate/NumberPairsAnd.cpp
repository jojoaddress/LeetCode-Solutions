#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> pairSums(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> cnt;
        vector<vector<int>> res;
        for (int i = 0; i < n;i++)
        {
            auto it = cnt.find(target - nums[i]);
            if(it!=cnt.end()&&it->second>0)
            {
                res.push_back({it->first,nums[i]});
                cnt[it->first]--;
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
    vector<int> nums = {2, 1, 8, 6, 5, 7, -1, 3, 5, 5};
    int target = 7;
    vector<vector<int>> res = sol.pairSums(nums,target);
    for(auto &pair:res)
    {
        cout<<pair[0]<<" "<<pair[1]<<endl;
    }
    return 0;
}