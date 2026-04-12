/*
 * 2023.12.08
 *
 * 跳跃游戏
 * 给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
 *
 * 解题思路为：每次都找下次能跳最远的，因为只有最远才是所有跳的可能性。
 * 其他思路：可以对每一个能作为起跳点的格子都尝试跳一次，把能跳到最远的距离不断更新，跳到最后为true
 */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool canJump(vector<int> &nums)
    {
        int len = nums.size() - 1;
        int i = 0;
        while (i < len)
        {
            int tmpMax = 0;
            int tmpJ = 0;
            if ((nums[i] + i) >= len)
                return true;
            for (int j = i + 1; j <= nums[i] + i; j++)
            {
                if (nums[j] + j >= tmpMax)
                {
                    tmpMax = nums[j] + j;
                    tmpJ = j;
                }
            }

            if (tmpMax == 0)
            {
                return false;
            }

            i = tmpJ;
        }
        return true;
    }
};

class Solution_plus
{
public:
    bool canJump(vector<int> &nums)
    {
        int i = 0;
        int k = 0;
        while (i < nums.size())
        {
            if (i > k)
                return false;
            k = max(k, i + nums[i]);
            i++;
        }
        return true;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {4, 2, 0, 0, 1, 1, 4, 4, 4, 0, 4, 0};
    cout << s->canJump(nums);
    return 0;
}