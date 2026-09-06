#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm> 
using namespace std;


class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> path;
        auto dfs = [&](this auto &&dfs, int start) -> void
        {
            res.push_back(path);
            unordered_set<int> uset;
            for (int i = start; i < nums.size();i++)
            {
                if(uset.find(nums[i])!=uset.end())
                    continue;
                uset.insert(nums[i]);
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return res;
    }
};