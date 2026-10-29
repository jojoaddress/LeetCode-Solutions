#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int jud(int i, int j, vector<vector<int>> &board)
    {

        int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
        int res = 0;
        for (int k = 0; k < 8; k++)
        {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x < 0 || x >= board.size() || y < 0 || y >= board[0].size())
                continue;
            if (board[x][y])
                res++;
        }
        if (res == 3)
            return 1;
        if (res == 2)
            return board[i][j];
        return 0;
    }

    void gameOfLife(vector<vector<int>> &board)
    {
        int m = board.size(), n = board[0].size();
        vector<vector<int>> copy(m, vector<int>(n));
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                copy[i][j] = board[i][j];

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                board[i][j] = jud(i, j, copy);
            }
        }
    }
};