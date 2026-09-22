#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> s(n + 1, 0);
        for (int i = 0; i < n;i++)
            s[i + 1] = s[i] + nums[i];

        int res = 0;
        unordered_map<int, int> mp;
        for(auto num:s)
        {
            res += mp.contains(num - k) ? mp[num-k] : 0;
            mp[num]++;
        }
        return res;
    }
};