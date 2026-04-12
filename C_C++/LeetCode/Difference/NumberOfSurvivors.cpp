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
    int maxAliveYear(vector<int> &birth, vector<int> &death)
    {
        int n = birth.size();
        map<int, int> d;
        for (int i = 0; i < n; i++)
        {
            int first = birth[i];
            int second = death[i];
            d[first]++;
            d[second + 1]--;
        }

        int ans = 0;
        int s = 0, s_max = INT_MIN;
        for (auto it = d.begin(); it != d.end(); ++it)
        {
            s += it->second;
            if (s > s_max)
            {
                s_max = s;
                ans = it->first;
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> birth = {1900, 1901, 1950};
    vector<int> death = {1948, 1951, 2000};
    int ans = sol.maxAliveYear(birth, death);
    cout << ans << endl; // Output: 1950
    return 0;
}