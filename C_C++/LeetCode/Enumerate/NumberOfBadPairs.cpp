#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// nums[i] - i=nums[j]-j
class Solution
{
public:
    long long countBadPairs(vector<int> &nums)
    {
        long long n = nums.size();
        long long maxN = n * (n - 1) / 2;
        long long res=0;
        unordered_map<long long , long long > cnt;
        for (int i = 0; i < n; i++)
        {
            long long  t = nums[i] - i;
            auto it = cnt.find(t);
            if(it!=cnt.end())
            {
                res+=cnt[t];
            }
            cnt[nums[i] - i]++;
        }
        return maxN - res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1,2,3,4,5};
    long long res = sol.countBadPairs(nums);
    cout << res << endl;
    return 0;
}