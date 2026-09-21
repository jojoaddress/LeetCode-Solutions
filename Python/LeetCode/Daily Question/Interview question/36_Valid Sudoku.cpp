#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    bool isValidSudoku(vector<vector<char>> &board)
    {
        vector<bitset<9>> row(9, bitset<9>());
        vector<bitset<9>> col(9, bitset<9>());
        vector<vector<bitset<9>>> block(3, vector<bitset<9>>(3, bitset<9>()));

        for (int i = 0; i < board.size(); i++)
        {
            for (int j = 0; j < board[0].size(); j++)
            {
                if (board[i][j] != '.')
                {
                    int n = board[i][j] - '1';
                    if (row[i][n] || col[j][n] || block[i / 3][j / 3][n])
                        return false;
                    row[i] |= 1 << n;
                    col[j] |= 1 << n;
                    block[i / 3][j / 3] |= 1 << n;
                }
            }
        }
        return true;
    }
};