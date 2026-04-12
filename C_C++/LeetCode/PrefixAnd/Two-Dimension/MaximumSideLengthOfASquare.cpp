#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxSideLength(vector<vector<int>> &mat, int threshold)
    {
        int n = mat.size();
        int m = mat[0].size();
        auto s = vector<vector<int>>(n+1, vector<int>(m+1));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + mat[i][j];

        int res = 0;
        int len = 0;
        for (int i = 0; i < n; i++)
        {
            len++;
            for (int j = 0; j < m; j++)
            {
                for (int k = res; k < len;k++)
                {
                    int row1 = i - k, col1 = j - k;
                    int row2 = i, col2 = j;
                    if(col1<0)
                        break;
                    int area = s[row2 + 1][col2 + 1] - s[row1][col2 + 1] - s[row2 + 1][col1] + s[row1][col1];
                    if(area<=threshold)
                    {
                        res = k + 1;
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<vector<int>> mat = {
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2},
        {1, 1, 3, 2, 4, 3, 2}};
    cout << s.maxSideLength(mat, 4) << endl;
    return 0;
}