#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution_
{
public:
    vector<bool> isArraySpecial(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<int> s(n + 1, 0);
        for (int i = 2; i <= n; i++)
        {
            if ((nums[i - 1] % 2 == 0 && nums[i - 2] % 2 == 0) || (nums[i - 1] % 2 != 0 && nums[i - 2] % 2 != 0))
            {
                s[i] = s[i - 1];
            }
            else
            {
                s[i] = s[i - 1] + 1;
            }
        }

        vector<bool> res;
        for (int i = 0; i < queries.size(); i++)
        {
            int k = queries[i][1] - queries[i][0];
            auto jud = [&](int l, int r)
            {
                return (s[r + 1] - s[l + 1] == k);
            };
            res.push_back(jud(queries[i][0], queries[i][1]));
        }
        return res;
    }
};
//另一种思路
class Solution {
public:
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries) 
    {
        int n = nums.size();
        vector<int> s(n + 1, 0);
        for (int i = 1; i < n;i++)
            s[i] = s[i - 1] + (nums[i - 1] % 2 == nums[i] % 2);
        vector<bool> res(queries.size());
        for (int i = 0; i < queries.size();i++)
        {
            res[i] =(s[queries[i][1]] == s[queries[i][0]]);
        }
        return res;
    }
};

int main()
{
    vector<int> nums = {3,4,1,2,6};
    vector<vector<int>> queries = {{0,4}};
    Solution sol;
    vector<bool> result = sol.isArraySpecial(nums, queries);
    for (bool b : result)
    {
        std::cout << (b ? "true" : "false") << std::endl;
    }
    return 0;
}