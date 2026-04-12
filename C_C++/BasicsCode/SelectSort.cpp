#include <iostream>
#include <math.h>
using namespace std;

void selectSort(int a[],int k)
{
    int i,j;
    for(i=0;i<k;i++)
    {
        int minIndex = i;
        for(j=i+1;j<k;j++)
        {
            if(a[minIndex]>a[j])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            swap(a[i],a[minIndex]);
        }
        
    }
}
int main()
{
    int a[9]={9,8,7,6,5,4,3,2,1};
    selectSort(a,9);
    return 0;
}
