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
    int evalRPN(vector<string> &tokens)
    {
        stack<int> stk;
        for (auto &c : tokens)
        {
            if (c == "*")
            {
                int num = stk.top();
                stk.pop();
                stk.top() *= num;
            }
            else if (c == "/")
            {
                int num = stk.top();
                stk.pop();
                stk.top() /= num;
            }
            else if (c == "+")
            {
                int num = stk.top();
                stk.pop();
                stk.top() += num;
            }
            else if (c == "-")
            {
                int num = stk.top();
                stk.pop();
                stk.top() -= num;
            }
            else
            {
                stk.push(stoi(c));
            }
        }
        return stk.top();
    }
};

int main()
{
    Solution sol;
    vector<string> tokens = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    cout << "Result of Reverse Polish Notation: " << sol.evalRPN(tokens) << endl;
    return 0;
}