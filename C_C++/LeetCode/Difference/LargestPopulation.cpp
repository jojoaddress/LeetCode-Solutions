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
    int maximumPopulation(vector<vector<int>> &logs)
    {
        map<int, int> d;
        for (auto &log : logs)
        {
            int first = log[0];
            int second = log[1];
            d[first]++;
            d[second]--;
        }
        int s = 0, s_max = INT_MIN;
        int ans = 0;
        for (auto &[index, num] : d)
        {
            s += num;
            if(s>s_max)
            {
                s_max = s;
                ans = index;
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> logs = {{1993, 1999}, {2000, 2010}};
    int ans = sol.maximumPopulation(logs);
    cout << ans << endl; // Output: 1993
    return 0;
}