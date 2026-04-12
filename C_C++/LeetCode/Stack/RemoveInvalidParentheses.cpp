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
    string minRemoveToMakeValid(string s)
    {
        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if (c == '(')
                cnt++;
            if (c == ')')
                cnt--;
            if (cnt < 0)
            {
                cnt = 0;
                s.erase(s.begin() + i);
                i--;
            }
        }
        if(cnt > 0)
        {
            for(int i=s.size()-1;i>=0;i--)
            {
                if(cnt==0)
                    break;
                if(s[i]=='(')
                {
                    s.erase(s.begin()+i);
                    cnt--;
                }
            }
        }
        return s;
    }
};

int main()
{
    Solution sol;
    string s = "))((";
    cout << "Valid parentheses string: " << sol.minRemoveToMakeValid(s) << endl;
    return 0;
}