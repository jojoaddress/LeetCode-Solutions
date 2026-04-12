#include <iostream>
#include <vector>
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
    void dfs(vector<int> &nums, vector<int> &temp, vector<vector<int>> &ans, int depth, int n)
    {
        ans.push_back(temp);
        if (depth == n)
        {
            return;
        }
        for (int i = depth; i < n; i++)
        {
            temp.push_back(nums[i]);
            dfs(nums, temp, ans, i + 1, n); // 注意这里的 i + 1
            temp.pop_back();
        }
    }
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> temp;
        vector<vector<int>> ans;
        dfs(nums, temp, ans, 0, nums.size());
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