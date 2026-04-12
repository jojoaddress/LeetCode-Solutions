#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// s[j] - s[i] = sum
//  sum % k == 0
// s[j] - s[i] = n*k, s[j] - n*k = s[i]
// s[j]%k=s[i]%k

class Solution
{
public:
    int subarraysDivByK(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + nums[i - 1];

        int ans = 0;
        unordered_map<int, int> cnt;
        cnt[0] = 1;
        for (int i = 1; i <= n;i++)
        {
            int mod = (s[i] % k + k) % k;
            ans += cnt.count(mod) > 0 ? cnt[mod] : 0;
            cnt[mod]++;
        }
        return ans;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {4,5,0,-2,-3,1};
    cout << s->subarraysDivByK(nums,5);
    return 0;
}
