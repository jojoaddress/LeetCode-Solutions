#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    void outPut(vector<vector<char>> res)
    {
        for (int i = 0; i < res.size(); i++)
        {
            for (int j = 0; j < res[0].size(); j++)
            {
                cout << res[i][j] << " ";
            }
            cout << endl;
        }
    }

    bitset<9> getPossibleNum(int x, int y)
    {
        return ~(rowBit[x] | colBit[y] | blockBit[x / 3][y / 3]);
    }

    void fillNum(int x, int y, int n, bool enable)
    {
        rowBit[x][n] = enable ? 1 : 0;
        colBit[y][n] = enable ? 1 : 0;
        blockBit[x / 3][y / 3][n] = enable ? 1 : 0;
    }

    pair<int, int> getNext(vector<vector<char>> &board)
    {
        int row = board.size();
        int col = board[0].size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == '.')
                {
                    return {i, j};
                }
            }
        }
        return {-1, -1};
    }

    bool isValidSudoku(vector<vector<char>> &board)
    {
        int row = board.size();
        int col = board[0].size();
        if (row != 9 || col != 9)
        {
            return;
        }
        rowBit = vector<bitset<9>>(9, bitset<9>());
        colBit = vector<bitset<9>>(9, bitset<9>());
        blockBit = vector<vector<bitset<9>>>(3, vector<bitset<9>>(3, bitset<9>()));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] != '.')
                {

                    int n = board[i][j] - '1';
                    if (rowBit[i][n] || colBit[j][n] || blockBit[i / 3][j / 3][n])
                        return false;
                    rowBit[i] |= (1 << n);
                    colBit[j] |= (1 << n);
                    blockBit[i / 3][j / 3] |= (1 << n);
                }
            }
        }
        return true;
    }

    bool dfs(vector<vector<char>> &board, int cnt)
    {
        if (cnt == 0)
        {
            return true;
        }
        pair<int, int> next = getNext(board);
        bitset<9> possibleNum = getPossibleNum(next.first, next.second);
        for (int i = 0; i < 9; i++)
        {
            if (possibleNum.test(i))
            {
                fillNum(next.first, next.second, i, true);
                board[next.first][next.second] = i + '1';
                if (dfs(board, cnt - 1))
                    return true;
                board[next.first][next.second] = '.';
                fillNum(next.first, next.second, i, false);
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        int row = board.size();
        int col = board[0].size();
        int cnt = 0;
        if (row != 9 || col != 9)
        {
            return;
        }
        rowBit = vector<bitset<9>>(9, bitset<9>());
        colBit = vector<bitset<9>>(9, bitset<9>());
        blockBit = vector<vector<bitset<9>>>(3, vector<bitset<9>>(3, bitset<9>()));
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] == '.')
                {
                    cnt++;
                    continue;
                }
                int n = board[i][j] - '1';
                rowBit[i] |= (1 << n);
                colBit[j] |= (1 << n);
                blockBit[i / 3][j / 3] |= (1 << n);
            }
        }
        dfs(board, cnt);
    }

private:
    vector<bitset<9>> rowBit;
    vector<bitset<9>> colBit;
    vector<vector<bitset<9>>> blockBit;
};

int main()
{
    vector<vector<char>> board =
        {
            {'5', '3', '.', '.', '.', '.', '.', '.', '.'},
            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    auto s = new Solution();
    s->solveSudoku(board);
    s->outPut(board);
    return 0;
}