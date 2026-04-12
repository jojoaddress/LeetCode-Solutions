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
    int findMaxK(vector<int>& nums) {
        int n = nums.size();
        int res = -1;
        unordered_map<int, int> cnt;
        for (int i = 0; i < n;i++)
        {
            auto it = cnt.find(-nums[i]);
            if(it!=cnt.end())
            {
                if(abs(nums[i])>res)
                    res = abs(nums[i]);
            }
            cnt[nums[i]]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {-10,8,6,7,-2,-3};
    int res = sol.findMaxK(nums);
    cout << res << endl;
    return 0;
}