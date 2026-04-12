/* 2024.1.19
 *
 * 编辑距离
 * 给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数 
 * 你可以对一个单词进行如下三种操作：
 * 插入一个字符
 * 删除一个字符
 * 替换一个字符
 * 
 * 本题还是利用动态规划，没什么好说的，画矩阵找规律
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int text1Len = word1.size();
        int text2Len = word2.size();
        vector<vector<int>> dp(text1Len + 1, vector<int>(text2Len + 1, 0));
        for (int i = 0; i <= text1Len; i++)
        {
            dp[i][0] = i;
        }
        for (int j = 0; j <= text2Len; j++)
        {
            dp[0][j] = j;
        }
        for (int i = 1; i <= text1Len; i++)
        {
            for (int j = 1; j <= text2Len; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    dp[i][j] =dp[i-1][j-1];// dp[i][j] 表示 text1[0:i-1] 和 text2[0:j-1]最少操作数

                }
                else
                {
                    dp[i][j] = min(dp[i-1][j-1],min(dp[i-1][j], dp[i][j - 1]))+1;
                }
            }
        }
        return dp[text1Len][text2Len];
    }
};

int main()
{
    Solution *s = new Solution();
    string text1 = "zoologicoarchaeologist";
    string text2 = "zoogeologist";
    cout << s->minDistance(text1, text2);
    return 0;
}