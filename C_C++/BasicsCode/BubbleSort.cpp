#include <iostream>
#include <math.h>
using namespace std;

//小->大
void BubbleSort01(int a[],int k)
{
    int i,j;
    for(i=0;i<k;i++)
    {
        for(j=k-1;j>i;j--)
        {
            if(a[j]<a[j-1])
            {
                swap(a[j],a[j-1]);
            }
        }
    }
}

void BubbleSort02(int a[],int k)
{
    int i,j;
    for(i=k-1;i>0;i--)
    {
        for(j=0;j<i;j++)
        {
            if(a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
}

int main()
{
    int a[9]={9,8,7,6,5,4,3,2,1};
    BubbleSort02(a,9);
    return 0;
}
