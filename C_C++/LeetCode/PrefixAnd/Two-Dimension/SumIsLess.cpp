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
    int countSubmatrices(vector<vector<int>> &grid, int k)
    {
        int n = grid.size();
        int m = grid[0].size();
        auto s = vector<vector<int>>(n + 1, vector<int>(m + 1));
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + grid[i][j];
                if (s[i + 1][j + 1] <= k)
                    res++;
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 0, 1}, {0, -2, 3}, {1, 2, 0}};
    int k = 2;
    int result = sol.countSubmatrices(grid, k);
    cout << "Number of submatrices with sum <= " << k << ": " << result << endl;
    return 0;
}