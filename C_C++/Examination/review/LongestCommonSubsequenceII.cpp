#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    string longestCommonSubsequence(string text1, string text2) {
        int n = text1.size();
        int m = text2.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n;i++)
        {
            for (int j = 1; j <= m;j++)
            {
                if(text1[i-1]==text2[j-1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        int len = dp[n][m];
        string s(len, ' ');
        int i = n, j = m;
        while (i > 0&&j>0)
        {
            if(text1[i-1]==text2[j-1])
            {
                s[--len] = text1[i - 1];
                i--;
                j--;
            }
            else if(dp[i-1][j]>dp[i][j-1])
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
    Solution sol;
    string text1 = "abcde";
    string text2 = "ace";
    string result = sol.longestCommonSubsequence(text1, text2);
    cout << "Longest Common Subsequence: " << result << endl;
    return 0;
}