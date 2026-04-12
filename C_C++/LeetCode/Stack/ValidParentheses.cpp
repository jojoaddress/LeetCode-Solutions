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
    bool isValid_(string s)
    {
        int n = s.size();
        stack<char> stk;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            {
                stk.push(s[i]);
                continue;
            }

            if (s[i] == ')' && (stk.empty() || stk.top() != '('))
                return false;
            else if (s[i] == '}' && (stk.empty() || stk.top() != '{'))
                return false;
            else if (s[i] == ']' && (stk.empty() || stk.top() != '['))
                return false;
            else
                stk.pop();
        }
        return stk.size() == 0;
    }
    bool isValid(string s)
    {
        unordered_map<char, char> mp = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        stack<char> stk;
        if (s.size() % 2 != 0)
            return false;
        for (auto &c : s)
        {
            if (mp.find(c) != mp.end())
            {
                stk.push(mp[c]);
            }
            else
            {
                if (stk.empty() || stk.top() != c)
                {
                    return false;
                }
                stk.pop();
            }
        }
        return stk.empty();
    }
};
int main()
{
    Solution sol;
    string s = "(";
    cout << (sol.isValid(s) ? "Valid" : "Invalid") << endl;
    return 0;
}