/* 2023.12.26
 *
 * 杨辉三角
 * res[i][j]=res[i-1][j-1]+res[i-1][j]   (i>2,i>j>1)
 *
 *
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> res(numRows);
        res[0] = {1};
        res[1] = {1, 1};
        if (numRows == 1)
        {
            return {{1}};
        }
        if (numRows == 2)
        {
            return {{1}, {1, 1}};
        }
        for (int i = 0; i < numRows; i++)
        {
            res[i].resize(i + 1);
        }
        for (int i = 2; i < numRows; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                res[i][j] = 1;
                if (j > 0 && j < i)
                    res[i][j] = (res[i - 1][j - 1] + res[i - 1][j]);
            }
        }
        
        return res;
    }
};

int main()
{
    Solution *s = new Solution();
    s->generate(5);
    return 0;
}