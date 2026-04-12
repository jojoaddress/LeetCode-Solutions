#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int uniquePaths(int m, int n)
    {
        int dp[m][n];
        fill(&dp[0][0], &dp[0][n], 1);
        fill(&dp[0][0], &dp[m][0], 1);
        for (int i = 1; i < m; i++)
        {
            for(int j = 1; j < n; j++)
            {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
        return dp[m-1][n-1];
    }
};

int main()
{
    Solution *s = new Solution();
    cout<<s->uniquePaths(3,2);
    return 0;
}