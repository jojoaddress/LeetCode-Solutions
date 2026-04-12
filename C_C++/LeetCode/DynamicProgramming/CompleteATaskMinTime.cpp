#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int minSessions(vector<int> &tasks, int sessionTime)
    {
        int n = tasks.size();
        int m = 1 << n;
        vector<int> sum(m);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0, k = 1 << i; j < k; j++)
            {
                sum[j | k] = sum[j] + tasks[i];
            }
        }

        vector<int> dp(m, n);
        dp[0] = 0;
        for (int s = 0; s < m; s++)
        {
            for (int sub = s; sub; sub = (sub - 1) & s)
            {
                if (sum[sub] <= sessionTime)
                {
                    dp[s] = min(dp[s], dp[s ^ sub] + 1);
                }
            }
        }
        return dp[m - 1];
    }
};

int main()
{
    Solution sol;
    vector<int> tasks = {1, 2, 3};
    int sessionTime = 3;
    cout << sol.minSessions(tasks, sessionTime) << endl;
    return 0;
}