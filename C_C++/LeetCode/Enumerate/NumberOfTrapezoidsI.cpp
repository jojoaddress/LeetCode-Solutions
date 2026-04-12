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
    int countTrapezoids(vector<vector<int>> &points)
    {
        const int MOD = 1'000'000'007;
        unordered_map<int, int> cnt;

        for (auto p : points)
            cnt[p[1]]++;

        long long ans = 0, s = 0;
        for (auto c : cnt)
        {
            long long k = 1LL * (c.second - 1) * c.second / 2;
            ans += k * s;
            s += k;
        }
        return ans % MOD;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> points = {{1, 0}, {2, 0}, {3, 0}, {2, 2}, {3, 2}};
    int res = sol.countTrapezoids(points);
    cout << res << endl;
    return 0;
}