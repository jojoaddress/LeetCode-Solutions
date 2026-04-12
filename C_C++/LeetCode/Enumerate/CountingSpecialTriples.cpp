#include <algorithm>
#include <iostream>
#include <map>
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
    int specialTriplets_1(vector<int> &nums)
    {
        int MOD = 1e9 + 7;
        int n = nums.size();
        unordered_map<int, int> cnt1;

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            unordered_map<int, int> cnt2;
            if (cnt1.count(nums[i] * 2) > 0)
            {
                for (int j = n - 1; j > i; j--)
                {
                    cnt2[nums[j]]++;
                }
                if (cnt2.count(nums[i] * 2) > 0)
                {
                    ans += cnt1[nums[i] * 2] * cnt2[nums[i] * 2] % MOD;
                }
            }
            cnt1[nums[i]]++;
        }
        return ans;
    }

    int specialTriplets(vector<int> &nums)
    {
        int MOD = 1e9 + 7;
        int n = nums.size();
        unordered_map<int, int> cnt1;
        unordered_map<int, int> cnt2;

        int ans = 0;
        for (int i = 0; i < n; i++)
            cnt2[nums[i]]++;
        for (int i = 0; i < n; i++)
        {
            cnt2[nums[i]]--;
            if (cnt1.count(nums[i] * 2) > 0 && cnt2[nums[i] * 2] > 0)
            {
                ans = (ans +  1LL * cnt1[nums[i] * 2] * cnt2[nums[i] * 2] % MOD) % MOD;
            }
            cnt1[nums[i]]++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {0,1,0,0};
    cout << sol.specialTriplets(nums) << endl; // Output: 1
    return 0;
}