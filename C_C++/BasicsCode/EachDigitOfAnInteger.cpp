/**
 * 给一个不多于 5 位的正整数，要求：①求出它是几位数；②分别打印出每一位数字；
 * 按逆序打印出各位数字，例如原数为 321，应输出 123。
*/

#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

vector<int> algNum(int n)
{
    int count = 0;
    vector<int> res;
    while(n)
    {
        int temp = n%10;
        res.push_back(temp);
        count++;
        n/=10;
    }
    return res;
}

int main()
{
    auto res = algNum(123456);
    for(auto it=res.begin(); it!=res.end(); it++)
    {
        cout << *it << " ";
    }
    cout<<endl;
    for(auto it=res.rbegin(); it!=res.rend(); it++)
    {
        cout << *it << " ";
    }
    return 0;
}