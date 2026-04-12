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
            for (int j = 0; j < res[0].size(); j++)
            {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }
    void dfs(vector<vector<int>> &res, vector<int> nums, vector<int> &tmp, vector<int> &tag, int depth, int n)
    {
        if (depth == n)
        {
            res.push_back(tmp);
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (!tag[i])
            {
                tag[i] = 1;
                tmp.push_back(nums[i]);
                dfs(res, nums, tmp, tag, depth + 1, n);
                tag[i] = 0;
                tmp.pop_back();
            }
        }
    }
    vector<vector<int>> permute(vector<int> &nums)
    {
        int size = nums.size();
        auto tag = vector<int>(size);
        vector<int> temp;
        vector<vector<int>> res;
        dfs(res, nums, temp, tag, 0, size);
        return res;
    }
};

int main()
{
    vector<int> a = {1, 2, 3};
    auto s = new Solution();
    auto res = s->permute(a);
    s->outPut(res);
}