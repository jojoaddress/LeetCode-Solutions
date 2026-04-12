#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    long long continuousSubarrays(vector<int> &nums)
    {
        int n = nums.size();
        deque<int> min_dq, max_dq;
        int left = 0;
        long long res = 0;
        for (int i = 0; i < n; i++)
        {
            while (!min_dq.empty() && nums[min_dq.back()] > nums[i])
                min_dq.pop_back();
            min_dq.push_back(i);

            while (!max_dq.empty() && nums[max_dq.back()] < nums[i])
                max_dq.pop_back();
            max_dq.push_back(i);

            while (abs(nums[min_dq.front()] - nums[max_dq.front()]) > 2)
            {
                if (min_dq.front() == left)
                    min_dq.pop_front();
                if (max_dq.front() == left)
                    max_dq.pop_front();
                left++;
            }

            if (abs(nums[min_dq.front()] - nums[max_dq.front()]) <= 2)
            {
                res += i - left + 1; // 以当前元素 nums[i] 为右端点的所有有效连续子数组的数量。
                cout << "i-left+1:" << i - left + 1 << " res: " << res << endl;
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {5, 4, 2, 4};
    cout << sol.continuousSubarrays(nums) << endl;
    return 0;
}
