#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class NumMatrix
{
public:
    NumMatrix(vector<vector<int>> &matrix)
    {
        int n = matrix.size();
        int m = matrix[0].size();
        s= vector<vector<int>>(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + matrix[i][j];
            }
        }
    }

    int sumRegion(int row1, int col1, int row2, int col2)
    {
        return s[row2 + 1][col2 + 1] - s[row2 + 1][col1] - s[row1][col2 + 1] + s[row1][col1];
    }

private:
    vector<vector<int>> s;
};

int main()
{   
    vector<vector<int>> matrix = {
        {3, 0, 1, 4, 2},
        {5, 6, 3, 2, 1},
        {1, 2, 0, 1, 5},
        {4, 1, 0, 1, 7},
        {1, 0, 3, 0, 5}};
    NumMatrix *obj = new NumMatrix(matrix);
    cout << obj->sumRegion(2, 1, 4, 3) << endl;
    cout << obj->sumRegion(1, 1, 2, 2) << endl;
    cout << obj->sumRegion(1, 2, 2, 4) << endl;
    return 0;
}