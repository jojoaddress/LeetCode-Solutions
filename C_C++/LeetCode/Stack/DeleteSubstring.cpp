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
    int minLength(string s)
    {
        int n = s.size();
        stack<char> str;
        for (int i = 0; i < n; i++)
        {
            if (str.empty())
            {
                str.push(s[i]);
                continue;
            }
            string temp = string() + str.top() + s[i];
            if (temp == "AB" || temp == "CD")
            {
                str.pop();
            }
            else
            {
                str.push(s[i]);
            }
        }
        return str.size();
    }
};

int main()
{
    Solution sol;
    string s = "ABFCACDB";
    cout << sol.minLength(s) << endl;
    return 0;
}