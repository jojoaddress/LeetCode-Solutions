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
    bool isValid(string s)
    {
        int n = s.size();
        string org = "abc";
        string str = "";
        for (int i = 0; i < n; i++)
        {
            str += string() + s[i];
            int len = str.size();
            if (len >= 3 && str.substr(len - 3, len) == org)
            {
                str.erase(len - 3);
            }
        }
        return str.size() == 0;
    }
};

int main()
{
    Solution sol;
    string s = "abccba";
    cout << (sol.isValid(s) ? "true" : "false") << endl;
    return 0;
}