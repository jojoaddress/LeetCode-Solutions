#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    bool isFactor(char a, char b)
    {
        if (a + 32 == b || a - 32 == b)
            return true;
        return false;
    }
    string makeGood(string s)
    {
        int n = s.size();
        stack<char> str;
        for (int i = 0; i < n; i++)
        {
            if (!str.empty() && isFactor(str.top(), s[i]))
            {
                str.pop();
            }
            else
            {
                str.push(s[i]);
            }
        }
        string res = "";
        while (!str.empty())
        {
            res += str.top();
            str.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};

int main()
{
    Solution sol;
    string s = "leEeetcode";
    cout << sol.makeGood(s) << endl;
    return 0;
}