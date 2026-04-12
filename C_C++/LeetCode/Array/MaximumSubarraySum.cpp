/* 2024.01.02
 *
 * 最大子数组和
 * 给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。子数组 是数组中的一个连续部分。
 * 
 * 一开始的滑动窗口思路，因有负数故行不通。
 * 下面的解决思路是题解的动态规划，dp[i]：表示以 nums[i] 结尾 的 连续 子数组的最大和。
 * dp[i]= dp[i−1]+nums[i], if dp[i−1]>0
          nums[i],         if dp[i−1]≤0
​ *
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int maxSubArray(vector<int> &nums)
    {
        
        int len = nums.size();
        int dp[len];
        dp[0] = nums[0];
        for (int i = 1; i < len; i++)
        {
            if (dp[i - 1] > 0)
            {
                dp[i] = dp[i - 1] + nums[i];
            }
            else
            {
                dp[i] = nums[i];
            }
        }

        int resMax = -dp[0];
        for (int i = 0; i < len; i++)
        {
            resMax = max(resMax, dp[i]);
        }

        return resMax;
    }
};

int main()
{
    Solution *s1 = new Solution();
    vector<int> str = {5,4,-1,7,8};
    s1->maxSubArray(str);
    return 0;
}