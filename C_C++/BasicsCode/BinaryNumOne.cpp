/**
 * 输出一个十进制数的二进制数形式中的1的个数。
 * 判断一个数是否为2的幂
*/

#include<iostream>
using namespace std;

int NumberOfOne(int n)
{
    int count=0;
    while(n)
    {
        if(n&1)
        {
            count++;
        }
        n=n>>1;
    }
    return count;
}

int main()
{
    int n=0;
    cout<<"Please input a number:";
    cin>>n;
    cout<<"The number of 1 in binary is:"<<NumberOfOne(n)<<endl;
    if(NumberOfOne(n)==1)
    {
        cout<<"It is a power of 2"<<endl;
    }
    return 0;
}