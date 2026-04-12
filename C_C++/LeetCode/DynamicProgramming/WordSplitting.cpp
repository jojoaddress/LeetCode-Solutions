#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    bool wordBreak(string s, vector<string> &wordDict)
    {
        unordered_set<string> wordString;
        for (auto s : wordDict)
        {
            wordString.insert(s);
        }

        int len = s.size();
        vector<int> dp(len + 1);
        dp[0] = true;
        for (int i = 1; i <= len; i++)
        {
            for (int j = 0; j < i; j++)
            {
                auto test = s.substr(j, i-j);
                if (dp[j] && (wordString.find(s.substr(j, i-j)) != wordString.end()))
                {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[len];
    }
};

int main()
{
    Solution *s = new Solution();
    string str = "leetcode";
    vector<string> word = {"leet","code"};
    cout << s->wordBreak(str, word);
    return 0;
}