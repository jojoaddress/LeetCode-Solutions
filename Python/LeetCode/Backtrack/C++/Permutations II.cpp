#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> dp(nums.size(), false);

        auto dfs = [&](this auto &&dfs, int start) -> void {
            if (start == nums.size())
            {
                res.push_back(path);
                return;
            }
            unordered_set<int> uset;
            for (int i = 0; i < nums.size();i++)
            {
                if(dp[i])
                    continue;
                if(uset.count(nums[i]))
                    continue;
                uset.insert(nums[i]);
                dp[i] = true;
                path.push_back(nums[i]);
                dfs(start + 1);
                path.pop_back();
                dp[i] = false;
            }
        };
        dfs(0);
        return res;
    }
};