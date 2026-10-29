#include <algorithm>
#include <iostream>
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
        stack<long long> nums; 
        stack<char> ops;
        int n = s.size();
        int i = 0;
        bool expectOperand = true;

        while (i < n)
        {
            if (s[i] == ' ')
            {
                i++;
                continue;
            }

            if (isdigit(s[i]))
            {
                long long num = 0; 
                while (i < n && isdigit(s[i]))
                    num = num * 10 + (s[i++] - '0');
                nums.push(num);
                expectOperand = false;
            }
            else if (s[i] == '(')
            {
                ops.push('(');
                i++;
                expectOperand = true;
            }
            else if (s[i] == ')')
            {
                while (ops.top() != '(')
                    eval(nums, ops);
                ops.pop();
                i++;
                expectOperand = false;
            }
            else
            {
                if (expectOperand && s[i] == '-')
                    nums.push(0);

                while (!ops.empty() && ops.top() != '(' &&
                       priority(ops.top()) >= priority(s[i]))
                    eval(nums, ops);

                ops.push(s[i]);
                i++;
                expectOperand = true;
            }
        }

        while (!ops.empty())
            eval(nums, ops);
        return (int)nums.top();
    }

private:
    int priority(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    void eval(stack<long long> &nums, stack<char> &ops)
    {
        long long b = nums.top();
        nums.pop();
        long long a = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        long long res = 0;
        if (op == '+')
            res = a + b;
        else if (op == '-')
            res = a - b;
        else if (op == '*')
            res = a * b;
        else if (op == '/')
            res = a / b;
        nums.push(res);
    }
};