/*
* 2023.11.03
* 移动零
* 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
* 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
*
* 第二种方法很巧妙，一次遍历，两个指针。只要遇到非零的数字，即填在数组前面。这样既保证了顺序，也最终得到了剩余多少个0。
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void moveZeroes(vector<int> &nums)
    {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left < right)
        {
            while (nums[left] != 0 && left < right)
                left++;
            while (nums[right] == 0 && left < right)
                right--;
            if (nums[left] == 0)
            {
                nums.erase(nums.begin() + left);
                nums.push_back(0);
            }
        }
    }
};

class SolutionPlus
{
public:
    void moveZeroes(vector<int> &nums)
    {
        int i=0,j=0;
        int n = nums.size();
        for(;i<n;i++)
        {
            if(nums[i]!=0) nums[j++]=nums[i];
        }
        for(;j<n;j++)
        {
            nums[j]=0;
        }
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {0,1,0,3,12};
    s->moveZeroes(nums);
    return 0;
}
