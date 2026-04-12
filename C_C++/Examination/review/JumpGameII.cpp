#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        int right = 0, end = 0, count = 0;
        for (int i = 0; i < n - 1; i++)
        {
            right = max(right, i + nums[i]);
            if (i == end)
            {
                end = right;
                count++;
            }
        }
        return count;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2, 3, 0, 1, 4};
    cout << sol.jump(nums) << endl;
    return 0;
}