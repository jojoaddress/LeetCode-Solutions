#include <iostream>
#include <vector>
#include <algorithm>
#include <functional> 
#include <numeric>
using namespace std;

class Solution {
public:
    int subsetXORSum(vector<int>& nums) {
        int n = nums.size();
        int ans = 0;
        int temp = 0;
        auto dfs = [&](auto &&self, int depth) -> void
        {
            ans+=temp;
            if(depth==n)
                return;
            for (int i = depth; i < n;i++)
            {
                temp ^= nums[i];
                self(self, i + 1);
                temp ^= nums[i];
            }
        };
        dfs(dfs,0);
        return ans;
    }
};