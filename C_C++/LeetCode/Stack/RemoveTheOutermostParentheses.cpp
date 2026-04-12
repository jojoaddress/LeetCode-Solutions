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
    string removeOuterParentheses(string s)
    {
        string res = "";
        stack<char> stk;
        for (auto &c : s)
        {
            if (c == ')')
                stk.pop();
            if (!stk.empty())
                res.push_back(c) ;
            if (c == '(')
                stk.push(c);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    string s = "(()())(())(()(()))";
    cout << sol.removeOuterParentheses(s) << endl;
    return 0;
}