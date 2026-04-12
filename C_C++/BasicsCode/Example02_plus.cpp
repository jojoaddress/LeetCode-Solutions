/**
 * 小->大
*/
#include <iostream>
#include <math.h>
using namespace std;

void bubbleSort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=n-1;j>i;j--)
        {
            if(a[j]<a[j-1])
            {
                swap(a[j],a[j-1]);
            }
        }
    }
}

void selectSort(int a[],int n)
{
    for(int i=0;i<n;i++)
    {
        int minIndex = i;
        for(int j=i+1;j<n;j++)
        {
            if(a[minIndex]>a[j])
            {
                minIndex=j;
            }
        }
        if(minIndex!=i)
        {
            swap(a[i],a[minIndex]);
        }
    }
}

int main()
{
    int a[]={9,8,7,6,5,4,3,2,1};
    int len = sizeof(a)/sizeof(a[0]);
    // bubbleSort(a,len);
    selectSort(a,len);
    for(int i=0;i<len;i++)
    {
        cout<<a[i]<<" ";
    }
}