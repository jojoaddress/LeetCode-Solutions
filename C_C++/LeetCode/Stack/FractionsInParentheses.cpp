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
    int scoreOfParentheses(string s)
    {
        stack<int> stk;
        stk.push(0);
        for(auto &c:s)
        {
            if(c=='(')
            {
                stk.push(0);
            }
            else
            {
                int v = stk.top();
                stk.pop();
                stk.top() += max(2 * v, 1);
            }
        }
        return stk.top();
    }
};

int main()
{
    Solution sol;
    string s = "(()(()))";
    cout << "Score of parentheses: " << sol.scoreOfParentheses(s) << endl;
    return 0;
}