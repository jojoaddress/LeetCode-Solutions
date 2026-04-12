#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int numSubarraysWithSum(vector<int> &nums, int goal)
    {
        int n = nums.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + nums[i - 1];

        int res = 0;
        unordered_map<int, int> cnt;
        for(auto sj : s)
        {
            auto p = cnt.find(sj - goal);
            res += p != cnt.end() ? p->second : 0;
            cnt[sj]++;
        }
        return res;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {1,1,-1,1,-1};
    int goal = 1;
    cout << s->numSubarraysWithSum(nums, goal);
    return 0;
}