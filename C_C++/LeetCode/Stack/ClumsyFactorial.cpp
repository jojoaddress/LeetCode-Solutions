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
    int clumsy(int n)
    {
        int index = 0;
        stack<int> num;
        num.push(n);
        for (int i = n - 1; i >= 1; i--)
        {
            if (index % 4 == 0)
            {
                num.top() *= i;
            }
            else if (index % 4 == 1)
            {
                num.top() /= i;
            }
            else if (index % 4 == 2)
            {
                num.push(i);
            }
            else if(index %4==3)
            {
                num.push(-i);
            }
            index++;
        }
        int res = 0;
        while(!num.empty())
        {
            res += num.top();
            num.pop();
        }
        return res;
    }
};

int main()
{
    Solution sol;
    int n = 10;
    cout << "Clumsy Factorial of " << n << " is: " << sol.clumsy(n) << endl;
    return 0;
}