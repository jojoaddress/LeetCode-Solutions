#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int minDeletion_(vector<int> &nums)
    {
        int n = nums.size();
        if (n == 0)
            return 0;
        stack<int> stk;
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            if (!stk.empty() && (stk.size() - 1) % 2 == 0 && stk.top() == nums[i])
            {
                res++;
                continue;
            }
            else
            {
                stk.push(nums[i]);
            }
        }
        if (stk.size() % 2 == 1)
            res++;
        return res;
    }

    int minDeletion__(vector<int> &nums)
    {
        int n = nums.size();
        int res = 0; // 删除操作数目
        for (int i = 0; i < n - 1; i++)
        {
            if ((i - res) % 2 == 0 && nums[i] == nums[i + 1])
            {
                res++;
            }
        }
        return (n - res) % 2 == 0 ? res : res + 1;
    }

    // 简单来讲，就是判断nums[i]是否符合条件时，看下栈是否为偶数
    // 如果是偶数，那么可能符合也可能不符合，所以要判断nums[i] == nums[i + 1]
    // 如果是奇数，则nums[i]和nums[i+1]一定能压入栈
    int minDeletion(vector<int> &nums)
    {
        int n = nums.size();
        int res = 0;
        stack<int> stk;

        for (int i = 0; i < n - 1; i++)
        {
            if ((i - res) % 2 == 0 && nums[i] == nums[i + 1])
            {
                res++;
            }
            else
            {
                stk.push(nums[i]);
            }
        }

        // 处理最后一个元素
        if ((n - 1 - res) % 2 == 0)
        {
            stk.push(nums[n - 1]);
        }

        // 如果最终栈大小为奇数，需要再删除一个元素
        if (stk.size() % 2 != 0)
        {
            res++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {3, 4, 1, 1, 2, 2, 3, 3};
    cout << sol.minDeletion(nums) << endl;
    return 0;
}