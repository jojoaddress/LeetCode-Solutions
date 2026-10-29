#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> cnt;
        for (int i = 0; i < nums.size();i++)
        {
            int need = target - nums[i];
            if(cnt.count(need))
                return {cnt[need], i};
            cnt[nums[i]] = i;
        }
        return {};
    }
};