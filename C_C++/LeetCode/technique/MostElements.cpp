/*
* 2023.11.02
* 多数元素
* 给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。
* 你可以假设数组是非空的，并且给定的数组总是存在多数元素。
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        unordered_map<int, int> hashtable;
        if (nums.size() == 1)
        {
            return nums[0];
        }
        for (int i = 0; i < nums.size(); ++i)
        {
            hashtable[nums[i]]++;

            if (hashtable[nums[i]] > (nums.size() / 2))
            {
                return nums[i];
            }
        }

        return {};
    }
};

class SolutionPlus
{
public:
    int majorityElement(vector<int> &nums)
    {
        unordered_map<int, int> counts;
        int majority = 0, cnt = 0;
        for (int num : nums)
        {
            ++counts[num];
            if (counts[num] > cnt)
            {
                majority = num;
                cnt = counts[num];
            }
        }
        return majority;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> a = {1, 3, 3, 3, 3, 4};
    int res = s->majorityElement(a);
    cout << res;
    return 0;
}