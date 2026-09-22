#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int left = 0;
        int sum = 0;
        int minLen = INT_MAX;
        for (int i = 0; i < n;i++)
        {
            sum += nums[i];
            while(sum>=target)
            {
                minLen = min(minLen, i - left + 1);
                sum -= nums[left];
                left++;
            }
        }
        return minLen==INT_MAX?0:minLen;
    }
};