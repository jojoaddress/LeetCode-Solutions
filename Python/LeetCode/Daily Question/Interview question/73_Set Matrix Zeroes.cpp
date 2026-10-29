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
    void setZeroes(vector<vector<int>> &matrix)
    {
        bool first_row = ranges::contains(matrix[0], 0);
        bool first_col = ranges::any_of(matrix, [](auto &row)
                                        { return row[0] == 0; });

        for (int i = 1; i < matrix.size(); i++)
        {
            for (int j = 1; j < matrix[0].size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    matrix[i][0] = 0;
                    matrix[0][j] = 0;
                }
            }
        }

        for (int i = 1; i < matrix.size(); i++)
        {
            for (int j = 1; j < matrix[0].size(); j++)
            {
                if (matrix[i][0]==0||matrix[0][j]==0)
                {
                    matrix[i][j] = 0;
                }
            }
        }
        if (first_col)
        {
            for (auto &row : matrix)
            {
                row[0] = 0;
            }
        }
        if (first_row)
        {
            ranges::fill(matrix[0], 0);
        }
    }
};