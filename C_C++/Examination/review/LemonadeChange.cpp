#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    bool lemonadeChange(vector<int> &bills)
    {
        int c5 = 0, c10 = 0;
        for (auto b : bills)
        {
            if (b == 5)
            {
                c5++;
            }
            else if (b == 10)
            {
                c5--;
                c10++;
            }
            else if (c10 > 0)
            {
                c5--;
                c10--;
            }
            else
            {
                c5 -= 3;
            }
            if (c5 < 0)
                return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    vector<int> bills = {5, 5, 5, 10, 5, 5, 10, 20, 20, 20};
    if (sol.lemonadeChange(bills))
        cout << "True";
    else
        cout << "False";
}