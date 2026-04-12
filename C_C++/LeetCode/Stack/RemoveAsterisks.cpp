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
    string removeStars(string s)
    {
        string res;
        for (int i = 0; i < s.size(); i++)
        {
            if(s[i]=='*')
            {
                res.erase(res.size()-1);
                continue;
            }
            res += s[i];
        }
        return res;
    }
};

int main()
{
    Solution sol;

    string s = "leet**cod*e";
    auto res = sol.removeStars(s);
    cout << res << endl;

    return 0;
}