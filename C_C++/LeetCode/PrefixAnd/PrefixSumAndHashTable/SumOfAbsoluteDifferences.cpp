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
    vector<int> getSumAbsoluteDifferences(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = nums[i - 1] + s[i - 1];

        vector<int> res;
        for (int i = 1; i <= n; i++)
        {
            int num = nums[i-1];
            int left = i * num - s[i];
            int right = s[n] - s[i] - (n - i) * num;
            res.push_back(left + right);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2, 3, 5};
    vector<int> res = sol.getSumAbsoluteDifferences(nums);
    for (int num : res)
        cout << num << " ";
    cout << endl;
    return 0;
}