#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int divide(int left, int right, vector<int> nums)
    {
        if (left == right)
            return nums[left];
        int mid = (left + right) / 2;
        int leftSum = divide(left, mid, nums);
        int rightSum = divide(mid + 1, right, nums);
        int midSum = crossSum(left, mid, right, nums);
        return max(max(leftSum, rightSum), midSum);
    }

    int crossSum(int left, int mid, int right, vector<int> nums)
    {
        int leftMax = INT_MIN, leftSum = 0;
        for (int i = mid; i >= left; i--)
        {
            leftSum += nums[i];
            leftMax = max(leftMax, leftSum);
        }

        int rightMax = INT_MIN, rightSum = 0;
        for (int i = mid + 1; i <= right; i++)
        {
            rightSum += nums[i];
            rightMax = max(rightMax, rightSum);
        }

        return leftMax + rightMax;
    }

    int maxSubArray_1(vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        return divide(0, nums.size() - 1, nums);
    }
    int maxSubArray(vector<int> &nums)
    {
        int sMin = 0, sum = 0, result = INT_MIN;
        for (auto num : nums)
        {
            sum += num;
            result = max(result, sum - sMin);
            sMin = min(sMin, sum);
        }
        return result;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum Subarray Sum: " << sol.maxSubArray(nums) << endl;
    return 0;
}