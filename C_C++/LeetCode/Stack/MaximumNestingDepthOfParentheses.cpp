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
    int maxDepth_(string s)
    {
        int res = 0;
        stack<char> stk;
        for (auto &c : s)
        {
            if (c == '(')
                stk.push(c);
            if (c == ')')
                stk.pop();
            if (!stk.empty())
            {
                int temp = stk.size();
                res = max(res, temp);
            }
        }
        return res;
    }
    int maxDepth(string s)
    {
        int left = 0;
        int res = 0;
        for (auto &c : s)
        {
            if (c == '(')
            {
                left++;
                res = max(res, left);
            }
            else if (c == ')')
            {
                left--;
            }
        }
        return res;
    }
};

int main()
{
    Solution solution;
    string s = "(1+(2*3)+((8)/4))+1";
    cout << "Maximum nesting depth of parentheses: " << solution.maxDepth(s) << endl;
    return 0;
}