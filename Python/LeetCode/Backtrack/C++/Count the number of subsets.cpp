#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        int maxNUm = 0;
        for (auto &num:nums)
        {
            maxNUm |= num;
        }
        int ans = 0;
        auto dfs = [&](auto &&self, int cur, int depth,bool used) -> void {
            if (depth==nums.size())
            {
                if(used && cur == maxNUm)
                    ans += 1;
                return;
            }

            self(self, cur, depth + 1, used);
            self(self, cur|nums[depth], depth + 1, true);
        };
        dfs(dfs, 0, 0, false);
        return ans;
    }
};