#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Solution
{
public:
    void outPut(vector<vector<int>> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[i].size(); j++)
            {
                cout << res[i][j] << " " << endl;
            }
            cout << "-----" << endl;
        }
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        int n = nums.size();
        vector<vector<int>> ans;
        vector<int> tmp;
        function<void(int)> dfs = [&](int depth)
        {
            ans.push_back(tmp);
            if (depth == n)
                return;
            for (int i = depth; i < n; i++)
            {
                tmp.push_back(nums[i]);
                dfs(i + 1);
                tmp.pop_back();
            }
        };
        dfs(0);
        return ans;
    }
};

int main()
{
    auto s = new Solution();
    vector<int> nums = {1, 2, 3, 4};
    auto ans = s->subsets(nums);
    s->outPut(ans);
    return 0;
}
