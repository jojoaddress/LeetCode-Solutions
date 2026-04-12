/* 2024.1.15
 *
 * 最长回文子串
 * 给你一个字符串 s，找到 s 中最长的回文子串。
 * 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 * 
 * 解法一：动态规划；
 * 解法二：中心扩展法；
 * 解法二更易理解。
 * 
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

class Solution
{
public:

    /**
     * @brief Finds the longest palindromic substring in a given string.
     * 
     * @param s The input string.
     * @return The longest palindromic substring found in the input string.
     */
    string longestPalindrome(string s)
    {
        vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
        string res;
        if (s.size() == 0)
        {
            return "";
        }
        if (s.size() == 1)
        {
            return s;
        }
        for (int i = 0; i < s.size(); i++)
        {
            dp[i][i] = 1;
        }
        int maxLen = 0;
        for (int R = 0; R < s.size(); R++)
        {
            for (int i = 0; i <= R; i++)
            {
                if (s[i] == s[R])
                {
                    if (R - i < 3)
                    {
                        dp[i][R] = 1;
                    }
                    else
                    {
                        dp[i][R] = dp[i + 1][R - 1];
                    }
                }
                else
                {
                    dp[i][R] = 0;
                }

                if (dp[i][R] == 1 && R - i + 1 > maxLen)
                {
                    maxLen = R - i + 1;
                    res = s.substr(i, maxLen);
                }
            }
        }
        return res;
    }
};

class Solutio_plus
{
public:
    pair<int, int> expandCenter(string s, int left, int right)
    {
        while (left >= 0 && right < s.size() && s[left] == s[right])
        {
            left--;
            right++;
        }
        return {left + 1, right - 1};
    }

    string longestPalindrome(string s)
    {
        int begin = 0;
        int end = 0;
        for (int i = 0; i < s.size(); i++)
        {
            auto [left1, right1] = expandCenter(s, i, i);
            auto [left2, right2] = expandCenter(s, i, i + 1);
            if (right1 - left1 > end - begin)
            {
                end = right1;
                begin = left1;
            }
            if (right2 - left2 > end - begin)
            {
                end = right2;
                begin = left2;
            }
        }
        return s.substr(begin,end-begin+1);
    }
};

int main()
{
    Solutio_plus *s = new Solutio_plus();
    string str = "babad";
    cout << s->longestPalindrome(str);
    return 0;
}