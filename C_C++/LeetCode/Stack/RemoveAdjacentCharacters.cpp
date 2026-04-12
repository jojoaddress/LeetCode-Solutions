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
    bool isJud(char a, char b)
    {
        int diff = abs(a - b);
        return diff == 1 || diff == 25;
    }
    string resultingString(string s)
    {
        int n = s.size();
        string str = "";
        for (int i = 0; i < n; i++)
        {
            if (!str.empty() && isJud(str.back(), s[i]))
            {
                str.erase(str.size() - 1);
            }
            else
            {
                str += s[i];
            }
        }

        return str;
    }
};

int main()
{
    Solution sol;
    string s = "iwioccwvpdtjntmbpsaz";
    cout << sol.resultingString(s) << endl;
    return 0;
}