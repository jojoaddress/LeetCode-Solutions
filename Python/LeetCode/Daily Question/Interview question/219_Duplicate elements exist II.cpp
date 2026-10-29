#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    bool containsNearbyDuplicate(vector<int> &nums, int k)
    {
        unordered_map<int, int> cnt;
        for (int i = 0; i < nums.size(); i++)
        {
            if (cnt.count(nums[i])&&(i-cnt[nums[i]])<=k)
            {
                return true;
            }
            cnt[nums[i]] = i;
        }
        return false;
    }
};