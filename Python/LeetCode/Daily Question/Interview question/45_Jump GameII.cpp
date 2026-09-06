#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int right = 0, end = 0;
        int res = 0;
        for (int i = 0; i < n-1;i++)
        {
            right = max(right, i + nums[i]);
            if(i==end)
            {
                end = right;
                res++;
            }
        }
        return res;
    }
};