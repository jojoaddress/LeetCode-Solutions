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
    string removeDuplicates(string s, int k)
    {
        stack<int> stk;
        for (int i = 0; i < s.size(); i++)
        {
            if (i == 0 || s[i] != s[i - 1])
            {
                stk.push(1);
            }
            else if (++stk.top() == k)
            {
                stk.pop();
                s.erase(i - k + 1, k);
                i = i - k;
            }
        }
        return s;
    }
};

int main()
{
    Solution sol;
    string s = "deeedbbcccbdaa";
    int k = 3;
    cout << sol.removeDuplicates(s, k) << endl; // Output: "aa"
    return 0;
}