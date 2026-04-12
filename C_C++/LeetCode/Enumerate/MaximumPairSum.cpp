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
    int maxNum(int num)
    {
        int res = 0;
        while(num)
        {
            int k = num % 10;
            res = max(res, k);
            num /= 10;
        }
        return res;
    }
    int maxSum(vector<int>& nums) {
        int n = nums.size();
        int res = -1;
        unordered_map<int, int> cnt;
        for (int i = 0; i < n;i++)
        {
            int k = maxNum(nums[i]);
            auto it = cnt.find(k);
            if(it!=cnt.end())
            {
                res = max(res, nums[i] + cnt[k]);
            }
            cnt[k] = cnt.count(k) > 0 ? max(cnt[k], nums[i]) : nums[i];
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1,2,3,4};
    cout << sol.maxSum(nums) << endl;
    return 0;
}