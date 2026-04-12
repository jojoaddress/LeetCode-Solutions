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
    long long numberOfRightTriangles(vector<vector<int>> &grid)
    {
        int n = grid[0].size();
        vector<int> col_sum(n, 0);
        long long ans = 0;

        for (auto &row : grid)
        {
            for (int j = 0; j < n; j++)
            {
                col_sum[j] += row[j];
            }
        }

        for (auto &row : grid)
        {
            int row_sum = reduce(row.begin(), row.end());
            for (int j = 0; j < n; j++)
            {
                if (row[j] == 1)
                    ans += (col_sum[j] - 1) * (row_sum - 1);
            }
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{0, 1, 0}, {0, 1, 1}, {0, 1, 0}};
    long long ans = sol.numberOfRightTriangles(grid);
    cout << ans << endl;
    return 0;
}