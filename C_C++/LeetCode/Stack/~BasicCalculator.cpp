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
    int calculate(string s)
    {
        vector<int> stk;
        char preChar = '+';
        int num = 0;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            char c = s[i];
            if (isdigit(c))
            {
                num = num * 10 + (c - '0');
            }
            if ((!isdigit(c) && c != ' ') || i == n - 1)
            {
                switch (preChar)
                {
                case '*':
                    stk.back() *= num;
                    break;
                case '/':
                    stk.back() /= num;
                    break;
                case '+':
                    stk.push_back(num);
                    break;
                case '-':
                    stk.push_back(-num);
                    break;
                default:
                    break;
                }
                num = 0;
                preChar = c;
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
};

int main()
{
    Solution sol;
    string s = " 3+5/2 ";
    cout << "Result of Basic Calculator: " << sol.calculate(s) << endl;
    return 0;
}