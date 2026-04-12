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
    int numberOfSubmatrices(vector<vector<char>> &grid)
    {
        int n = grid.size();
        int m = grid[0].size();
        auto s = vector<vector<vector<int>>>(n + 1, vector<vector<int>>(m + 1, vector<int>(2)));
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s[i + 1][j + 1][0] = s[i + 1][j][0] + s[i][j + 1][0] - s[i][j][0];
                s[i + 1][j + 1][1] = s[i + 1][j][1] + s[i][j + 1][1] - s[i][j][1];
                if (grid[i][j] != '.')
                {
                    s[i + 1][j + 1][grid[i][j] & 1]++;
                }
                if (s[i + 1][j + 1][0] && (s[i + 1][j + 1][0] == s[i + 1][j + 1][1]))
                {
                    res++;
                }
            }
        }

        return res;
    }
};