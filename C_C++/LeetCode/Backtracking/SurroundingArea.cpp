/**
 * 被围绕的区域
 * 看起来比较复杂，其实
 * 第 1 步：把四周有 O的地方都替换成为 -，在四周进行 floodfill 算法（染色）；
 * 第 2 步：再从头到尾遍历一遍，把 O 换成 X，把 - 换成 O。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<char>> &board, int x, int y, bool pre)
    {
        if (x < 0 || y < 0 || x >= rowSize || y >= colSize)
            return;

        if (board[x][y] != 'O')
            return;
        if (board[x][y] == 'O' && pre)
        {
            board[x][y] = '-';
        }
        if (board[x][y] == 'O' && !pre)
        {
            board[x][y] = 'X';
        }
        int dx[] = {-1, 0, 1, 0};
        int dy[] = {0, 1, 0, -1};

        for (int i = 0; i < 4; i++)
        {
            dfs(board, x + dx[i], y + dy[i], pre);
        }
    }

    void solve(vector<vector<char>> &board)
    {
        colSize = board[0].size();
        rowSize = board.size();
        for (int i = 0; i < rowSize; i++)
        {
            if (board[i][0] == 'O')
            {
                dfs(board, i, 0, true);
            }
            if (board[i][colSize - 1] == 'O')
            {
                dfs(board, i, colSize - 1, true);
            }
        }

        for (int i = 0; i < colSize; i++)
        {
            if (board[0][i] == 'O')
            {
                dfs(board, 0, i, true);
            }
            if (board[rowSize - 1][i] == 'O')
            {
                dfs(board, rowSize - 1, i, true);
            }
        }

        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (board[i][j] == 'O')
                {
                    dfs(board, i, j, false);
                }
            }
        }

        for (int i = 0; i < rowSize; i++)
        {
            for (int j = 0; j < colSize; j++)
            {
                if (board[i][j] == '-')
                {
                    board[i][j] = 'O';
                }
            }
        }
    }

private:
    int colSize;
    int rowSize;
};

int main()
{
    vector<vector<char>> board = {

        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'},
    };
    auto s = new Solution();
    s->solve(board);
    return 0;
}