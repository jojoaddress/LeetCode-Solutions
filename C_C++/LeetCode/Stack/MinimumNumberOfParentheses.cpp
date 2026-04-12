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
    int minAddToMakeValid_1(string s)
    {
        int res = 0;
        unordered_map<char, char> mp = {{'(', ')'}};
        stack<char> stk;
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
                    res++;
                }
                else
                {
                    stk.pop();
                }
            }
        }
        return stk.size() + res;
    }

    int minAddToMakeValid(string s)
    {
        int left = 0;
        int res = 0;
        for (auto &c : s)
        {
            if(c=='(')
                left++;
            else
            {
                if(left>0)
                    left--;
                else
                    res++;
            }
        }
        return res+left;
    }
};

int main()
{
    Solution solution;
    string s = "())";
    cout << solution.minAddToMakeValid(s) << endl; // Output: 3
    return 0;
}