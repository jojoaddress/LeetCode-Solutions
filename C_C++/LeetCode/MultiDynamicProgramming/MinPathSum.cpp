/* 2024.01.12
 * 
 * 最小路径和
 * 给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
 * 说明：每次只能向下或者向右移动一步。
 * 
 * 一次过，其实就是数学公式，甚至可以说是找规律
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution
{
public:
    int minPathSum(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i != 0 && j != 0)
                {
                    grid[i][j] = min(grid[i - 1][j], grid[i][j - 1]) + grid[i][j];
                }
                else if (j != 0)
                {
                    grid[0][j] += grid[0][j - 1];
                }
                else if (i != 0)
                {
                    grid[i][0] += grid[i - 1][0];
                }
            }
        }
        return grid[m - 1][n - 1];
    }
};

int main()
{
    Solution *s = new Solution();
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << s->minPathSum(grid);
    return 0;
}