#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    bool checkEqualPartitions(vector<int>& nums, long long target) {
        long long product = std::accumulate(nums.begin(), nums.end(), 1LL, std::multiplies<long long>());
        if (product / target != target || product % target != 0) return false;
        auto dfs = [&](auto &&self, long long mul,int depth) -> bool {
            if (mul == target)
                return true;
            if (mul > target)
                return false;
            for (int i = depth; i < nums.size();i++)
            {
                mul *= nums[i];
                if(self(self, mul, i + 1))
                    return true;
                mul /= nums[i];
            }
            return false;
        };
        return dfs(dfs, 1, 0);
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {2, 3, 4, 6};
    long long target = 12;
    bool result = solution.checkEqualPartitions(nums, target);
    cout << (result ? "True" : "False") << endl; // Output: True
    return 0;
}