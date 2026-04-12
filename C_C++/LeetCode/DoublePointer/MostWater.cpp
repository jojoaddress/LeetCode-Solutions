/*2023.11.30
 *
 * 盛水最多的容器
 * 给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0) 和 (i, height[i]) 。
 * 找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
 * 返回容器可以储存的最大水量。
 * 说明：你不能倾斜容器。
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int begin = 0;
        int end = height.size() - 1;
        int size = height.size();
        int mArea = -1;
        for (; begin < size; begin++)
        {
            for (end = size - 1; end > begin; end--)
            {
                int minSide = min(height[begin], height[end]);
                int area = (end - begin) * minSide;
                if (area > mArea)
                {
                    mArea = area;
                }
            }
        }
        return mArea;
    }
};

class SolutionPlus
{
public:
    int maxArea(vector<int> &height)
    {
        int begin = 0;
        int end = height.size() - 1;
        int size = height.size();
        int mArea = -1;

        while (begin < end)
        {
            int minSide = min(height[begin], height[end]);
            int area = (end - begin) * minSide;
            if (area > mArea)
            {
                mArea = area;
            }

            if(height[begin] > height[end])
            {
                end--;
            }
            else
            {
                begin++;
            }
        }
        return mArea;
    }
};

int main()
{
    SolutionPlus *s = new SolutionPlus();
    vector<int> nums = {1,8,6,2,5,4,8,3,7};
    cout << s->maxArea(nums);
    return 0;
}