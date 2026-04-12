#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + nums[i - 1];

        unordered_map<int, int> cnt;
        bool jud = false;
        cnt[0] = 0;
        for (int i = 1; i <= n;i++)
        {
            long long mod = (s[i] % k + k) % k;
            if(cnt.count(mod) > 0 && i - cnt[mod] >= 2)
                jud = true;
            else if(cnt.count(mod) == 0)
                cnt[mod] = i;
        }
        return jud;
    }
};


int main()
{
    auto s = new Solution;
    vector<int> nums = {0};
    cout << s->checkSubarraySum(nums,1);
    return 0;
}
