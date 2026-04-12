/**
 * 二分法求区间内方程的根
 *
 */
#include <iostream>
#include <math.h>
using namespace std;

class Solution
{
public:
    float equation(float x)
    {
        // return 2.0 * x * x * x - 4 * x * x + 3 * x - 6;
        return (x - 1) * (x - 9) * (x - 6);
    }
    float solve(float left, float right)
    {
        auto f1 = equation(left);
        auto f2 = equation(right);
        if (f1 == 0.0f)
            return left;
        if (f2 == 0.0f)
            return right;
        if (f1 * f2 > 0.0f)
            return -1;
        while (abs(right - left) >= 0.000001)
        {
            float x = (left + right) / 2.0f;
            float f = equation(x);
            if (f1 * f < 0)
            {
                right = x;
                f2 = f;
            }
            else
            {
                left = x;
                f1 = f;
            }
        }
        return (left + right) / 2.0f;
    }
};

int main()
{
    Solution s;
    cout << s.solve(3, 9) << endl;
    return 0;
}