/**
 * 求出一共有多少片连续的水洼
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void dfs(vector<vector<char>> &board, int x, int y)
    {
        if (x < 0 || x >= row || y < 0 || y >= col)
        {
            return;
        }
        if (board[x][y] != 'W')
            return;

        board[x][y] = '.';

        // 8个方向
        int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
        int dy[] = {-1, 1, 0, -1, 1, -1, 1, 0};
        for (int i = 0; i < 8; i++)
        {
            dfs(board, x + dx[i], y + dy[i]);
        }
    }
    int getNumber(vector<vector<char>> &board)
    {
        int res = 0;
        row = board.size();
        col = board[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == 'W')
                {
                    dfs(board, i, j);
                    res++;
                }
            }
        }
        return res;
    }

private:
    int row;
    int col;
};

int main()
{
    vector<vector<char>> board = {{'W', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.', '.'},
                                  {'.', 'W', 'W', 'W', '.', '.', '.', '.', '.', 'W', 'W', 'W'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', '.', '.'},
                                  {'W', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'},
                                  {'W', 'W', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'},
                                  {'W', '.', '.', '.', '.', '.', '.', '.', '.', 'W', 'W', '.'}};
    auto s = new Solution();
    cout << s->getNumber(board);
    return 0;
}