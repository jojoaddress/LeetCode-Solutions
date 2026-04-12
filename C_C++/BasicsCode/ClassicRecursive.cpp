#include<iostream>
using namespace std;
int callBack(int n)
{
    if(n==1) return 1;
    else if(n==2) return 2;
    else
    {
        return callBack(n-1)+callBack(n-2);
    }
}
//1 2 3 5 8 13
int main()
{
    int n;
    cin>>n;
    cout<<callBack(n);
}