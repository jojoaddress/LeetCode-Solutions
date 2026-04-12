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
    int maxDistance(vector<vector<int>> &arrays)
    {
        int n = arrays.size();
        int mn = INT_MAX / 2, mx = INT_MIN / 2;
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            auto a = arrays[i];
            res = max(res, max(mx - a[0], a.back() - mn));
            mx = max(mx, a.back());
            mn = min(mn, a[0]);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> arrays = {{1, 2, 3}, {4, 5}, {1, 2, 3}};
    cout << sol.maxDistance(arrays) << endl; // Output: 4
    return 0;
}
