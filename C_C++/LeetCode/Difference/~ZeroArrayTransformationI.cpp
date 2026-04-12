#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isZeroArray_(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        diff[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            diff[i] = nums[i] - nums[i - 1];
        }

        for (auto &q : queries)
        {
            int first = q[0];
            int second = q[1];
            diff[first]--;
            diff[second + 1]++;
        }

        int s = 0;
        for (int i = 0; i < n; i++)
        {
            s += diff[i];
            if (s > 0)
                return false;
        }
        return true;
    }

    //代码实现时，计算的是「区间减一」执行的次数。累加差分数组，可以得到在 nums[i] 处减一的次数 s。
    bool isZeroArray(vector<int> &nums, vector<vector<int>> &queries)
    {
        int n = nums.size();
        vector<int> diff(n + 1, 0);
        for (auto &q : queries)
        {
            int first = q[0];
            int second = q[1];
            diff[first]++;
            diff[second + 1]--;
        }

        int s = 0;
        for (int i = 0; i < n;i++)
        {
            s += diff[i];
            if(nums[i]-s>0)
                return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 0, 1};
    vector<vector<int>> queries = {{0, 2}};
    bool ans = sol.isZeroArray(nums, queries);
    cout << (ans ? "true" : "false") << endl; // Output: false
    return 0;
}