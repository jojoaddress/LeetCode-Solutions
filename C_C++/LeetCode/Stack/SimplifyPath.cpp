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
    string simplifyPath(string path)
    {
        vector<string> stk;
        istringstream ss(path);
        string s;
        while (getline(ss, s, '/'))
        {
            if (s.empty() || s == ".")
                continue;
            if (s != "..")
            {
                stk.push_back(s);
            }
            else if (!stk.empty())
            {
                stk.pop_back();
            }
        }
        string res;
        for(auto &s:stk)
        {
            res += '/';
            res += s;
        }
        return res == "" ? "/" : res;
    }
};

int main()
{
    Solution sol;
    string path = "/a/./b/../../c/";
    string res = sol.simplifyPath(path);
    cout << res << endl;
    return 0;
}