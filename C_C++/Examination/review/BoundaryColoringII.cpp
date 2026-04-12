#include <iostream>
#include <vector>
using namespace std;

class Solution
{
private:
    vector<vector<bool>> visited;
    vector<vector<bool>> border;
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

public:
    void dfs(int x, int y, vector<vector<int>> grid, int oldColor)
    {
        int n = grid.size();
        int m = grid[0].size();
        if (x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] != oldColor)
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
            dfs(x + dx[i], y + dy[i], grid, oldColor);
        }
        return;
    }
    vector<vector<int>> colorBorder(vector<vector<int>> &grid, int row, int col, int color)
    {
        int n = grid.size();
        int m = grid[0].size();
        visited = vector<vector<bool>>(n, vector<bool>(m, false));
        border = vector<vector<bool>>(n, vector<bool>(m, false));
        dfs(row, col, grid, grid[row][col]);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if(border[i][j])
                    grid[i][j] = color;
            }
        }
        return grid;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 1}, {1, 2}};
    int row = 0, col = 0, color = 3;
    vector<vector<int>> result = sol.colorBorder(grid, row, col, color);
    cout << "Colored Border Grid:" << endl;
    for (const auto &row : result)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
    return 0;
}