#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    stack<char> buildStack(string s)
    {
        stack<char> res;
        for (auto &c : s)
        {
            if(c=='#')
            {
                if(res.size()>0)
                    res.pop();
                continue;
            }
            res.push(c);
        }
        return res;
    }
    bool backspaceCompare(string s, string t)
    {
        stack<char> s_st = buildStack(s);
        stack<char> t_st = buildStack(t);

        return s_st == t_st;
    }
};

int main()
{
    Solution sol;
    string s = "a##c", t = "#a#c";
    cout << sol.backspaceCompare(s, t) << endl;
    return 0;
}