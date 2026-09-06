#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<int> path;
        vector<vector<int>> res;
        vector<int> nums(n);
        iota(nums.begin(), nums.end(), 1);

        auto dfs = [&](auto &&self, int start) -> void {
            if(path.size()==k)
            {
                res.push_back(path);
                return;
            }
            if(start==n)
                return;
            self(self, start + 1);

            path.push_back(nums[start]);
            self(self, start + 1);
            path.pop_back();
        };
        dfs(dfs, 0);
        return res;
    }
};