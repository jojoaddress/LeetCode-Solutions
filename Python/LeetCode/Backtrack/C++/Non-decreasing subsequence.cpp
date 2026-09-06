#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    vector<vector<int>> findSubsequences(vector<int> &nums)
    {
        vector<vector<int>> res;
        vector<int> path;
        auto dfs = [&](this auto &&dfs, int start) -> void
        {
            if (path.size() >= 2)
                res.push_back(path);
            unordered_set<int> used;
            for (int i = start; i < nums.size(); i++)
            {
                if (used.count(nums[i])) continue;
                if (!path.empty() && path.back() > nums[i])
                    continue;
                used.insert(nums[i]);
                path.push_back(nums[i]);
                dfs(i + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return res;
    }
};