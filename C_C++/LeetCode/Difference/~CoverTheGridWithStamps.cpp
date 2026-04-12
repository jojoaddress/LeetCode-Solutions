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

// 二维矩阵a的区域十1操作，等价于更新差分矩阵d中4个位置的差分值。
/*
i2, j2：表示当前枚举的印章覆盖区域的右下角单元格（循环里 i2 从 stampHeight 到 m，j2 从 stampWidth 到 n）。
i1 = i2 - stampHeight + 1，j1 = j2 - stampWidth + 1：分别是该印章覆盖区域的左上角行列索引（即印章放置的起始行和起始列）。
*/
class Solution
{
public:
    bool possibleToStamp(vector<vector<int>> &grid, int stampHeight, int stampWidth)
    {
        int m = grid.size(), n = grid[0].size();

        // 1. 计算 grid 的二维前缀和
        vector<vector<int>> s(m + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + grid[i][j];
            }
        }

        // 2. 计算二维差分
        vector<vector<int>> d(m + 2, vector<int>(n + 2, 0));
        for (int i2 = stampHeight; i2 <= m; i2++)
        {
            for (int j2 = stampWidth; j2 <= n; j2++)
            {
                int i1 = i2 - stampHeight + 1;
                int j1 = j2 - stampWidth + 1;
                if (s[i2][j2] - s[i1 - 1][j2] - s[i2][j1 - 1] + s[i1 - 1][j1 - 1] == 0)
                {
                    d[i1][j1]++;
                    d[i1][j2 + 1]--;
                    d[i2 + 1][j1]--;
                    d[i2 + 1][j2 + 1]++;
                }
            }
        }
        // 3. 还原二维差分矩阵对应的计数矩阵（原地计算）
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                d[i + 1][j + 1] += d[i][j + 1] + d[i + 1][j] - d[i][j];
                if (d[i + 1][j + 1] == 0 && grid[i][j] == 0)
                    return false;
            }
        }
        return true;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}};
    int stampHeight = 4, stampWidth = 3;
    bool res = sol.possibleToStamp(grid, stampHeight, stampWidth);
    cout << (res ? "true" : "false") << endl;
    return 0;
}