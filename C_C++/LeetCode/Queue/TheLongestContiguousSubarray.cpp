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
    int longestSubarray(vector<int> &nums, int limit)
    {
        int n = nums.size();
        deque<int> min_q,max_q;
        int res = 0;
        int left = 0;
        for (int i = 0; i < n; i++)
        {
            while (!min_q.empty() && nums[min_q.back()] >= nums[i])
            {
                min_q.pop_back();
            }
            min_q.push_back(i);
            while (!max_q.empty() && nums[max_q.back()] <= nums[i])
            {
                max_q.pop_back();
            }
            max_q.push_back(i);

            while (nums[max_q.front()] - nums[min_q.front()] > limit)
            {
                if (min_q.front() == left)
                {
                    min_q.pop_front();
                }
                if (max_q.front() == left)
                {
                    max_q.pop_front();
                }
                left++;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {10,1,2,4,7,2};
    int limit = 5;
    cout << sol.longestSubarray(nums, limit) << endl; // 4
    return 0;
}
