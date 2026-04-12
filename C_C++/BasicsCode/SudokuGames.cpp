/**
 * 解数独:
 * 第一次用bitset的小伙伴，需要注意的一点是bitset的存储方式，索引零对应的是存储的最后一位，cout输出和按照索引输出会得到互为倒序的结果~
 */
#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    bitset<9> getPossibleStatus(int x, int y)
    {
        return ~(rowBit[x] | colBit[y] | cellBit[x / 3][y / 3]);
    }

    void fillNum(int x, int y, int n, bool enable)
    {
        rowBit[x][n] = enable ? 1 : 0;
        colBit[y][n] = enable ? 1 : 0;
        cellBit[x / 3][y / 3][n] = enable ? 1 : 0;
    }

    pair<int, int> getNext(vector<vector<char>> &board)
    {
        int minCnt = 10;
        pair<int, int> res;
        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[i].size(); j++)
            {
                if (board[i][j] == '.')
                {
                    auto tempCnt = getPossibleStatus(i, j);
                    if (tempCnt.count() < minCnt)
                    {
                        minCnt = tempCnt.count();
                        res = {i, j};
                    }
                }
            }
        }
        return res;
    }

    bool dfs(vector<vector<char>> &board, int cnt)
    {
        if (cnt == 0)
            return true;

        auto next = getNext(board);
        auto bits = getPossibleStatus(next.first, next.second);
        for (int n = 0; n < bits.size(); n++)
        {
            if (bits.test(n))
            {
                fillNum(next.first, next.second, n, true);
                board[next.first][next.second] = n + '1';
                if (dfs(board, cnt - 1))
                    return true;
                fillNum(next.first, next.second, n, false);
                board[next.first][next.second] = '.';
            }
        }
        return false;
    }

    void solveSudoku(vector<vector<char>> &board)
    {
        int rowCount = board.size();
        int colCount = board.empty() ? 0 : board[0].size();
        if (rowCount != 9 || colCount != 9)
            return;
        rowBit = vector<bitset<9>>(9, bitset<9>());
        colBit = vector<bitset<9>>(9, bitset<9>());
        cellBit = vector<vector<bitset<9>>>(3, vector<bitset<9>>(3, bitset<9>()));
        int cnt = 0;
        for (int i = 0; i < rowCount; i++)
        {
            for (int j = 0; j < colCount; j++)
            {
                if (board[i][j] == '.')
                {
                    cnt++;
                    continue;
                }
                int n = board[i][j] - '1';
                rowBit[i] |= (1 << n);
                colBit[j] |= (1 << n);
                cellBit[i / 3][j / 3] |= (1 << n);
            }
        }
        dfs(board, cnt);
    }

private:
    vector<bitset<9>> rowBit;
    vector<bitset<9>> colBit;
    vector<vector<bitset<9>>> cellBit;
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
    return 0;
}