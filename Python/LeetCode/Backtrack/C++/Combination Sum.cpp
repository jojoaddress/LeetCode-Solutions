#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        auto dfs = [&](auto &&self, int target, int start) -> void {
            if (target==0)
            {
                res.push_back(path);
                return;
            }
            if (target<0)
                return;
            for (int i = start; i < candidates.size();i++)
            {
                path.push_back(candidates[i]);
                self(self, target - candidates[i], i);
                path.pop_back();
            }
        };
        dfs(dfs, target, 0);
        return res;
    }
};

int main() {
    Solution solution;
    vector<int> candidates = {2, 3, 6, 7};
    int target = 7;
    vector<vector<int>> result = solution.combinationSum(candidates, target);
    
    for (const auto& combination : result) {
        cout << "[";
        for (size_t i = 0; i < combination.size(); ++i) {
            cout << combination[i];
            if (i < combination.size() - 1) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }
    
    return 0;
}