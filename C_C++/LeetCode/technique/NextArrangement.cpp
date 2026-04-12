/* 2023.12.25
 *
 * 下一个排列
 * 熬了半天做出来个高效率击败100%的，一看答案怎么还有人投机取巧用了库函数啊。。。。。
 *
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int len = nums.size();
        int left = len - 2;
        int right = len - 1;
        if (len == 1 || len == 0)
        {
            return;
        }

        while (nums[left] >= nums[right] && left > 0)
        {
            left--;
            right--;
        }

        if (left == 0 && nums[0] > nums[1])
        {
            sort(nums.begin(), nums.end());
            return;
        }
        int turningP = left + 1;
        left = len - 2;
        right = len - 1;
        if (nums[left] >= nums[right])
        {
            int tmpMin = 99999;
            int minLeft = 99999;

            if (nums[right] > nums[turningP - 1])
            {
                tmpMin = nums[right];
                minLeft = right;
            }

            while (nums[left] >= nums[right] && left > 0)
            {
                if (nums[left] > nums[turningP - 1] && nums[left] < tmpMin)
                {
                    tmpMin = nums[left];
                    minLeft = left;
                }
                left--;
                right--;
            }
            if (minLeft < len)
            {
                swap(nums[turningP - 1], nums[minLeft]);
                sort(nums.begin() + turningP, nums.end());
            }
        }
        else if (nums[left] < nums[right])
        {
            swap(nums[left], nums[right]);
        }
    }
};

class Solution_plus
{
public:
    void nextPermutation(vector<int> &nums)
    {
        next_permutation(nums.begin(), nums.end());
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> a = {1, 1};
    s->nextPermutation(a);
    return 0;
}