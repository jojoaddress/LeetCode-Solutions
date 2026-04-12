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
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        int n = nums.size();
        deque<int> q;
        vector<int> res(n - k + 1);
        for (int i = 0; i < n; i++)
        {
            while (!q.empty() && nums[q.back()] <= nums[i])
            {
                q.pop_back();
            }
            q.push_back(i);
            int left = i - k + 1;
            if (q.front() < left)
            {
                q.pop_front();
            }
            if (left >= 0)
            {
                res[left] = nums[q.front()];
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;
    vector<int> result = sol.maxSlidingWindow(nums, k);
    for (int i : result)
    {
        cout << i << " ";
    }
    return 0;
}
