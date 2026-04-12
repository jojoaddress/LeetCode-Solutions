#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<int>> grid, int oldColor, int x, int y)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y]||grid[x][y] != oldColor)
            return;
        visited[x][y] = true;

        if (x == 0 || x == n - 1 || y == 0 || y == m - 1)
            border[x][y] = true;
        else
            for (int i = 0; i < 4; i++)
            {
                if (grid[x + dx[i]][y + dy[i]] != oldColor)
                    border[x][y] = true;
            }

        for (int i = 0; i < 4; i++)
        {
            dfs(grid, oldColor, x + dx[i], y + dy[i]);
        }
        return;
    }
    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        int n = grid.size(), m = grid[0].size();
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        border = vector<vector<bool>>(n, vector<bool>(m, false));
        dfs(grid, grid[row][col], row, col);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (border[i][j])
                    grid[i][j] = color;
            }
        }
        return grid;
    }

private:
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};
    vector<vector<bool>> visited;
    vector<vector<bool>> border;
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
    int row = 1, col = 1, color = 2;
    vector<vector<int>> result = sol.colorBorder(grid, row, col, color);
    for (const auto &r : result)
    {
        for (const auto &c : r)
        {
            cout << c << " ";
        }
        cout << endl;
    }
    return 0;
}