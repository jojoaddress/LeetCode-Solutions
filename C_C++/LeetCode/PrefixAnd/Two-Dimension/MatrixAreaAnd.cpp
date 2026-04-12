#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixBlockSum(vector<vector<int>>& mat, int k) {
        int n = mat.size();
        int m = mat[0].size();
        s = vector<vector<int>>(n + 1, vector<int>(m + 1));
        for (int i = 0; i < n;i++)
            for (int j = 0; j < m;j++)
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + mat[i][j];

        vector<vector<int>> ans(n, vector<int>(m));
        for (int i = 0; i < n;i++)
        {
            for (int j = 0; j < m;j++)
            {
                int row1 = i - k >= 0 ? i - k : 0;
                int col1 = j - k >= 0 ? j - k : 0;
                int row2 = i + k < n ? i + k : n - 1;
                int col2 = j + k < m ? j + k : m - 1;
                ans[i][j] = s[row2 + 1][col2 + 1] - s[row2 + 1][col1] - s[row1][col2 + 1] + s[row1][col1];
            }
        }
        return ans;
    }
private:
    vector<vector<int>> s;
};

/*
1 2 3
4 5 6
7 8 9
*/
int main()
{
    vector<vector<int>> mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    int k = 1;
    Solution sol;
    vector<vector<int>> ans = sol.matrixBlockSum(mat, k);
    for (auto &row : ans)
    {
        for (auto &num : row)
            cout << num << " ";
        cout << endl;
    }
    return 0;
}