#include <algorithm>
#include <iostream>
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
    vector<long long> minOperations(vector<int> &nums, vector<int> &queries)
    {
        int n = nums.size();
        int m = queries.size();
        sort(nums.begin(), nums.end());
        vector<long long> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = nums[i - 1] + s[i - 1];

        vector<long long> res;
        for (int i = 0; i < m; i++)
        {
            int q = queries[i];
            auto it = std::lower_bound(nums.begin(), nums.end(), q);
            long long j = static_cast<long long>(it - nums.begin());
            long long left = j * q - s[j];
            long long right = s[n] - s[j] - (n - j) * q;
            res.push_back(left + right);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {3, 1, 6, 8};
    vector<int> queries = {1, 5};
    vector<long long> res = sol.minOperations(nums, queries);
    for (long long num : res)
        cout << num << " ";
    cout << endl;
    return 0;
}