#include <iostream>
#include <string>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> path;
        vector<int> nums(9);
        iota(nums.begin(), nums.end(), 1);

        auto dfs = [&](this auto &&dfs, int start,int cur) -> void {
            if(path.size()==k&&cur==0)
            {
                res.push_back(path);
                return;
            }
            if(start==9||cur<0||path.size()>k)
                return;

            dfs(start + 1, cur);

            path.push_back(nums[start]);
            dfs(start + 1, cur - nums[start]);
            path.pop_back();
        };
        dfs(0, n);
        return res;
    }
};

int main()
{
    Solution sol;
    auto result = sol.combinationSum3(3, 7);
    for(const auto &v : result)
    {
        for(int i : v)
            cout << i << " ";
        cout << endl;
    }
    return 0;   
}