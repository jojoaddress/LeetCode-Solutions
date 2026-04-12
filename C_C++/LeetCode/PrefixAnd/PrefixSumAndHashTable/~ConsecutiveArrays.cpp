#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// nums[i]如果是0当成-1
// 如果 sum 已经在 Map 中出现过，说明从上一次出现该 sum 的位置 p->second + 1 到当前位置 i 之间，前缀和没有变化。
// 这意味着这段子数组内 0 和 1 的数量相等（因为 0 变成 -1，只有 0 和 1 数量相等时前缀和才会回到原来的值）。
class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int ans = 0;
        unordered_map<int, int> cnt;
        cnt[0] = -1;
        for (int i = 0; i < n;i++)
        {
            sum += nums[i] ? 1 : -1;
            auto p = cnt.find(sum);
            if(p!=cnt.end())
                ans = max(ans,i-p->second);
            else
                cnt[sum]=i;
        }
        return ans;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {0,1,1,1,1,1,0,0,0};
    cout << s->findMaxLength(nums);
    return 0;
}