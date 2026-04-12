#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class solution
{
public:
    string longestSubsequence_1(string s1, string s2)
    {
        int n = s1.size();
        int m = s2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        int len = dp[n][m];
        string s(len, ' ');
        int i = n, j = m;
        while (i > 0 && j > 0)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                s[--len] = s1[i - 1];
                i--;
                j--;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                i--;
            }
            else
            {
                j--;
            }
        }
        return s;
    }
};

int main()
{
    solution sol;
    string s1;
    string s2;
    cin >> s1 >> s2;
    string res = sol.longestSubsequence_1(s1, s2);
    cout << res << endl;
    return 0;
}