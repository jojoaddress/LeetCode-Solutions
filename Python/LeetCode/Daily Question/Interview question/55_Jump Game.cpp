#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int right = 0;
        int n = nums.size();
        for (int i = 0; i < n;i++)
        {
            if(i>right)
                return false;
            right = max(right, i + nums[i]);
        }
        return true;
    }
};