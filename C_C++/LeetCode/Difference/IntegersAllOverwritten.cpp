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
    bool isCovered(vector<vector<int>> &ranges, int left, int right)
    {
        int d[52]={};
        for (auto &r : ranges)
        {
            int first = r[0];
            int second = r[1];
            d[first]++;
            d[second + 1]--;
        }
        int s = 0;
        for (int i = 0; i <= right;i++)
        {
            s += d[i];
            if(i>=left&&s<=0)
                return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> ranges = {{1, 2}, {3, 4}, {5, 6}};
    int left = 2, right = 5;
    bool ans = sol.isCovered(ranges, left, right);
    cout << (ans ? "true" : "false") << endl; // Output: true
    return 0;
}