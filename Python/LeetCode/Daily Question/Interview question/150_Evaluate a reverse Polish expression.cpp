#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for(auto &s:tokens)
        {
            if(s=="+")
            {
                int num = stk.top();
                stk.pop();
                stk.top() += num;
            }
            else if(s=="-")
            {
                int num = stk.top();
                stk.pop();
                stk.top() -= num;
            }
            else if(s=="*")
            {
                int num = stk.top();
                stk.pop();
                stk.top() *= num;
            }
            else if(s=="/")
            {
                int num = stk.top();
                stk.pop();
                stk.top() /= num;
            }
            else
            {
                stk.push(stoi(s));
            }
        }
        return stk.top();
    }
};