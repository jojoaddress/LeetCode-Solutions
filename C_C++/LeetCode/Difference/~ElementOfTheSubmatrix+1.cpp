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
    vector<vector<int>> rangeAddQueries(int n, vector<vector<int>> &queries)
    {
        vector<vector<int>> d(n + 2, vector<int>(n + 2, 0));
        for (auto &q : queries)
        {
            int i1 = q[0];
            int j1 = q[1];
            int i2 = q[2];
            int j2 = q[3];
            d[i1][j1]++;
            d[i1][j2 + 1]--;
            d[i2 + 1][j1]--;
            d[i2 + 1][j2 + 1]++;
        }
        vector<vector<int>> res(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                res[i + 1][j + 1] = res[i + 1][j] + res[i][j + 1] - res[i][j] + d[i][j];
            }
        }
        res.erase(res.begin());
        for (auto &row : res)
        {
            row.erase(row.begin());
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int n = 3;
    vector<vector<int>> queries = {{1, 1, 2, 2}, {0, 0, 1, 1}};
    vector<vector<int>> res = sol.rangeAddQueries(n, queries);
    for (auto &row : res)
    {
        for (auto &val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}