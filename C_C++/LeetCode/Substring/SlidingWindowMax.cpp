/* 2023.12.21
 *
 * 滑动窗口最大值
 * 给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。
 * 返回滑动窗口中的最大值 。
 * 
 * 此题虽然一开始想到了最大堆，但对c++库函数熟悉程度不够，一直在用make_heap、push_heap等函数，没有想到priority_queue优先级队列，引以为戒。
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> res;
        priority_queue<pair<int, int>> stackMax;
        for (int i = 0; i < k; i++)
        {
            stackMax.emplace(nums[i], i);
        }
        res.push_back(stackMax.top().first);

        for (int i = k; i < nums.size(); i++)
        {
            stackMax.emplace(nums[i], i);
            while (stackMax.top().second <= i - k)
            {
                stackMax.pop();
            }
            res.push_back(stackMax.top().first);
        }
        return res;
    }
};


int main()
{
    Solution *s1 = new Solution();
    vector<int> str = {1, -1};
    s1->maxSlidingWindow(str, 1);
    return 0;
}