#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int len = nums.size();
    }
    void InsertSort(vector<int> &a, int n,int dk) // 递增
    {
        int i,j;
        for(i=dk+1;i<=n;i++)
        {
            if(a[i]<a[i-dk])
            {
                a[0] = a[i];
                for(j=i-dk;j>0&&a[j]>a[0];j-=dk)
                {
                    a[j+dk] = a[j];
                }
                a[j+dk] = a[0];
            }
        }
    }

    void ShellSort(vector<int> &a)
    {
        int n = a.size();
        int dk = n/2;
        while(dk>0)
        {
            InsertSort(a,n,dk);
            dk/=2;
        }
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> a={0,3,1,9,0,4};
    s->InsertSort(a,5,1);
    return 0;
}