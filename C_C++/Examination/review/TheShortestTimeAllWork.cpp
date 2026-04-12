#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int minimumTimeRequired(vector<int> &jobs, int k)
    {
        int n = jobs.size();
        int m = 1 << n;
        vector<int> sum(m);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0, temp = 1 << i; j < temp; j++)
            {
                sum[j | temp] = sum[j] + jobs[i];
            }
        }
        vector<vector<int>> dp(k, vector<int>(m));
        for (int i = 0; i < m; i++)
            dp[0][i] = sum[i];
        for (int i = 1; i < k; i++)
        {
            for (int j = 0; j < m; j++)
            {
                int minTime = INT_MAX;
                for (int sub = j; sub; sub = (sub - 1) & j)
                {
                    minTime = min(minTime, max(dp[i - 1][j ^ sub], sum[sub]));
                }
                dp[i][j] = minTime;
            }
        }
        return dp[k - 1][m - 1];
    }
};

int main()
{
    Solution sol;
    vector<int> jobs = {3, 2, 3};
    int k = 3;
    cout << sol.minimumTimeRequired(jobs, k) << endl;
    return 0;
}