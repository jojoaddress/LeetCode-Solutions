/*
* 2023.11.01
* 只出现一次的数字
* 给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
* 你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
*
* Soluton是先排序，在利用奇偶性质判断出那个“奇数”。SolutonPlus则是非常牛逼的利用了异或运算。
*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int singleNumber(vector<int> &nums)
    {
        sort(nums.begin(), nums.end(), less<int>());

        int i = 0;
        if (nums.size() == 1)
        {
            return nums[0];
        }

        while (i < nums.size() - 1)
        {
            if (nums[i] != nums[i + 1])
            {
                break;
            }
            i += 2;
        }
        return nums[i];
    }
};

class SolutonPlus
{
public:
    int singleNumber(vector<int> &nums)
    {
        int ans = nums[0];
        if (nums.size() > 1)
        {
            for (int i = 1; i < nums.size(); i++)
            {
                ans = ans ^ nums[i];
            }
        }
        return ans;
    }
};

int main()
{
    vector<int> nums = {2, 1};
    SolutonPlus *s = new SolutonPlus();
    cout << s->singleNumber(nums) << endl;
    return 0;
}
