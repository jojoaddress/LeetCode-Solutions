// 乘积最大子数组
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        if (nums.size() == 1)
        {
            return nums[0];
        }
        int maxNum = 1;
        int minNum = 1;
        int maxRes = INT_MIN;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] < 0)
            {
                int temp = maxNum;
                maxNum = minNum;
                minNum = temp;
            }
            maxNum = max(nums[i], maxNum * nums[i]);
            minNum = min(nums[i], minNum * nums[i]);
            maxRes = max(maxNum, maxRes);
        }
        return maxRes;
    }
};

int main()
{
    vector<int> nums = {2, -5, -2, -4, 3};
    auto s = new Solution;
    cout << s->maxProduct(nums);
}