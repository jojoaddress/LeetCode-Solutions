/*
统计能整除数字的位数

示例：
输入：num = 121
输出：2
解释：121 可以被 1 整除，但无法被 2 整除。由于 1 出现两次，所以返回 2 。

*/

#include <iostream>
#include <string>
using namespace std;

class Solution
{
public:
    int countDigits(int num)
    {
        string strNum = to_string(num);
        int len = strNum.size();
        const char *charNum = strNum.c_str();
        int res = 0;
        for (int i = 0; i < len; i++)
        {
            int tempNum = charNum[i] - '0';

            if ((num % tempNum) == 0)
            {
                res++;
            }
        }

        return res;
    }
};

class SolutonBest
{
public:
    int countDigits(int num)
    {
        int n = num;
        int res = 0;
        while (n != 0)
        {
            res += num % (n % 10) == 0;
            n /= 10;
        }
        return res;
    }
};

int main()
{
    /*     Solution *s = new Solution();
        cout << s->countDigits(111) << endl;
     */
    SolutonBest *best = new SolutonBest();
    cout << best->countDigits(111) << endl;
    return 0;
}