#include <algorithm>
#include <iostream>
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
    // 超时
    int maxAbsoluteSum_(vector<int> &nums)
    {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + nums[i - 1];

        int ans_max = INT_MIN;
        for (int i = 0; i <= n; i++)
        {
            for (int j = i + 1; j <= n; j++)
            {
                if (abs(s[j] - s[i]) > ans_max)
                    ans_max = abs(s[j] - s[i]);
            }
        }
        return ans_max;
    }

    // 动态规划 s[i]=s[i-1]+num[i]
    int maxAbsoluteSum__(vector<int> &nums)
    {
        int n = nums.size();

        int sMax = 0, sMin = 0;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            sMax = max(sMax, 0) + nums[i];
            sMin = min(sMin, 0) + nums[i];
            ans = max(ans, max(abs(sMax), abs(sMin)));
        }
        return ans;
    }

    // 前缀和
    int maxAbsoluteSum(vector<int> &nums)
    {
        int n = nums.size();
        int sMax = 0, sMin = 0;
        int s = 0;
        for (int i = 0; i < n; i++)
        {
            s += nums[i];
            sMax = max(sMax, s);
            sMin = min(sMin, s);
        }
        return sMax - sMin;
    }
};

int main()
{
    vector<int> nums = {-3, -5, -3, -2, -6, 3, 10, -10, -8, -3, 0, 10, 3, -5, 8, 7, -9, -9, 5, -8};
    auto s = new Solution;
    cout << s->maxAbsoluteSum(nums);
    return 0;
}
