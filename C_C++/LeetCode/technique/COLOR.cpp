/*
*2023.11.30
*颜色分类
*给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
*我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
*必须在不使用库内置的 sort 函数的情况下解决这个问题。
*
*头一次击败100%用户
*/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void sortColors(vector<int> &nums)
    {
        int color[3] = {0};
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] == 0)
            {
                color[0]++;
            }
            else if (nums[i] == 1)
            {
                color[1]++;
            }
            else
            {
                color[2]++;
            }
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (i < color[0])
                nums[i] = 0;
            if (i >= color[0] && i < color[0] + color[1])
                nums[i] = 1;
            if (i >= color[0] + color[1] && i < nums.size())
                nums[i] = 2;
        }
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {2,0,2,1,1,0};
    s->sortColors(nums);
    return 0;
}