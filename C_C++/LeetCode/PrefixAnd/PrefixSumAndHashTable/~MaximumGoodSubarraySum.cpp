#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 子数组 a[i..j] 的元素和为s[j+1]−s[i]
// 1. minS.find(x + k)和minS.find(x - k)是为了找到以前是否出现过a[i] = a[j] + k和a[i] = a[j] - k
// 2. 最后一个if，是为了维护键值为a[i]下的s[i]的最小值
// 3. sum是不包含当前的a[j]的，所以sum + x - it->second才能得出a[i...j]的和
class Solution
{
public:
    long long maximumSubarraySum(vector<int> &nums, int k)
    {
        long long ans = LLONG_MIN, sum = 0;
        unordered_map<int, long long> minS;
        for (auto x : nums)
        {
            auto it = minS.find(x + k);
            if (it != minS.end())
                ans = max(ans, sum + x - it->second);

            it = minS.find(x - k);
            if (it != minS.end())
                ans = max(ans, sum + x - it->second);

            it = minS.find(x);
            if (it == minS.end() || sum < it->second)
                minS[x] = sum;

            sum += x;
        }
        return ans == LLONG_MIN ? 0 : ans;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    cout << s->maximumSubarraySum(nums, 1);
    return 0;
}
