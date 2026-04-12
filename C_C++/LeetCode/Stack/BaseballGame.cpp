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
    bool isIntegerWithPositive(const std::string &str)
    {
        std::regex integer_pattern("^-?\\d+$");
        return std::regex_match(str, integer_pattern);
    }
    int calPoints_(vector<string> &operations)
    {
        stack<int> res;
        int sum = 0;
        for (auto &op : operations)
        {
            if (isIntegerWithPositive(op))
            {
                res.push(stoi(op));
            }
            if (op == "+")
            {
                int n1 = res.top();
                res.pop();
                int n2 = res.top();
                res.pop();
                res.push(n2);
                res.push(n1);
                res.push(n1 + n2);
            }
            if (op == "D")
            {
                int n = res.top();
                res.push(n * 2);
            }
            if (op == "C")
            {
                res.pop();
            }
        }

        while (!res.empty())
        {
            sum += res.top();
            res.pop();
        }
        return sum;
    }
    int calPoints(vector<string> &operations)
    {
        vector<int> res;
        for (auto &op : operations)
        {
            switch (op[0])
            {
            case '+':
                res.push_back(res.back() + res[res.size() - 2]);
                break;
            case 'D':
                res.push_back(res.back() * 2);
                break;
            case 'C':
                res.pop_back();
                break;
            default:
                res.push_back(stoi(op));
                break;
            }
        }
        return accumulate(res.begin(), res.end(), 0);
    }
};

int main()
{
    Solution sol;
    vector<string> operations = {"5", "-2", "4", "C", "D", "9", "+", "+"};
    cout << sol.calPoints(operations) << endl; // Output:27
    return 0;
}