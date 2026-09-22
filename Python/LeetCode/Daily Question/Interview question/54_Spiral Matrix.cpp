#include <iostream>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    static constexpr int DIR[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<int> spiralOrder(vector<vector<int>> &matrix)
    {
        int m = matrix.size(), n = matrix[0].size();
        int len = m * n;
        int i = 0, j = -1;
        vector<int> ans;
        for (int t = 0; ans.size() < len; t = (t + 1) % 4)
        {
            for (int step = 0; step < n; step++)
            {
                i += DIR[t][0];
                j += DIR[t][1];
                ans.push_back(matrix[i][j]);
            }
            m--;
            swap(m, n);
        }
        return ans;
    }
};