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
    int numberOfPoints(vector<vector<int>> &nums)
    {
        int d[102] = {};
        for (auto &num : nums)
        {
            int first = num[0];
            int second = num[1];
            d[first]++;
            d[second+1]--;
        }
        int ans = 0;
        int s = 0;
        for (int i = 0; i < 101; i++)
        {
            s = d[i] + s;
            if (s > 0)
                ans++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> nums = {{3, 6}, {1, 5}, {4, 7}};
    int ans = sol.numberOfPoints(nums);
    cout << ans << endl; // Output: 7
    return 0;
}