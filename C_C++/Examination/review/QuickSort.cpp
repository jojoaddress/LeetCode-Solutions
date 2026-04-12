#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    void quickSort(vector<int> &num,int left,int right)
    {
        if(left>=right)
            return;
        int mid = partSort(num, left, right);
        quickSort(num, left, mid - 1);
        quickSort(num, mid + 1, right);
    }
    int partSort(vector<int> &num,int left,int right)
    {
        int key = left;
        while(left<right)
        {
            while(right>left&&num[right]>=num[key])
                right--;
            while(right>left&&num[left]<=num[key])
                left++;
            swap(num[left], num[right]);
        }
        swap(num[left], num[key]);
        return left;
    }
private:
};

int main()
{
    Solution s;
    vector<int> nums = {3, 5, 1, 4, 2};
    s.quickSort(nums, 0, nums.size() - 1);
    for (int num : nums)
        cout << num << " ";
    return 0;
}