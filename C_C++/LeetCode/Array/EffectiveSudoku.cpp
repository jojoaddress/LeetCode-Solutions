#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    // bool hasDuplicate(const vector<bitset<9>> &bits)
    // {
    //     unordered_set<bitset<9>> bitset;
    //     for (const auto &bit : bits)
    //     {
    //         auto res = bitset.insert(bit);
    //         if(!res.second) return true;
    //     }
    //     return false;
    // }
    bool isValidSudoku(vector<vector<char>> &board)
    {
        rowBit = vector<bitset<9>>(9, bitset<9>());
        colBit = vector<bitset<9>>(9, bitset<9>());
        blockBit = vector<vector<bitset<9>>>(3, vector<bitset<9>>(9, bitset<9>()));

        int row = rowBit.size();
        int col = colBit.size();
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                if (board[i][j] != '.')
                {
                    int n = board[i][j] - '1';
                    if (rowBit[i][n] || colBit[j][n] || blockBit[i / 3][j / 3][n])
                        return false;
                    rowBit[i] |= 1 << n;
                    colBit[j] |= 1 << n;
                    blockBit[i / 3][j / 3] |= 1 << n;
                }
            }
        }
        return true;
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
    cout << s->isValidSudoku(board) << endl;
    return 0;
}