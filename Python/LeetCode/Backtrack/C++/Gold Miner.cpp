#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    int getMaximumGold(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        int maxR = 0;
        int dx[4] = {0, 0, 1, -1};
        int dy[4] = {1, -1, 0, 0};

        int totalGold = 0;
        for (auto &row : grid)
            for (int v : row)
                totalGold += v;
        if (totalGold == 0)
            return 0;

        vector<vector<bool>> v(n, vector<bool>(m, false));
        auto dfs = [&](this auto &dfs, int x, int y, int res)
        {
            if (x < 0 || x >= n || y < 0 || y >= m)
                return;
            if (grid[x][y] == 0 || v[x][y])
                return;
            res += grid[x][y];
            if (res > maxR)
            {
                maxR = res;
                if (maxR == totalGold)
                    return;
            }

            v[x][y] = true;
            for (int i = 0; i < 4; i++)
            {
                dfs(x + dx[i], y + dy[i], res);
                if (maxR == totalGold)
                    return;
            }
            v[x][y] = false;
        };
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] != 0)
                {
                    dfs(i, j, 0);
                    if (maxR == totalGold)
                        return maxR;
                }
            }
        }
        return maxR;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> grid = {{0, 6, 0}, {5, 8, 7}, {0, 9, 0}};
    int res = s.getMaximumGold(grid);
    cout << res << endl;
    return 0;
}