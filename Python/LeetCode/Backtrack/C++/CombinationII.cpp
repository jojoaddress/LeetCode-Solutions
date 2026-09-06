#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        ranges::sort(candidates);

        auto dfs = [&](this auto &&dfs, int start ,int cur) -> void {
            if(cur == 0)
            {
                res.push_back(path);
                return;
            }
            if(start>=candidates.size()||cur<0)
                return;

            path.push_back(candidates[start]);
            dfs(start + 1, cur - candidates[start]);
            path.pop_back();

            int x = candidates[start];
            while (start < candidates.size() && candidates[start] == x) {
                start++;
            }
            dfs(start, cur);
        };
        dfs(0, target);
        return res;
    }
};