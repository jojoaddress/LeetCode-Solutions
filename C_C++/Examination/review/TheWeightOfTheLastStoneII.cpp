#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


//x+y=sum,求最小=/x-y/=/sum-y-y/=/sum-2*y/,即求y最接近sum/2
class Solution {
public:
    int lastStoneWeightII(vector<int>& stones) {
        int n = stones.size();
        int sum = 0;
        for(auto stone:stones)
            sum += stone;
        int target = sum / 2;
        vector<int> dp(target + 1, 0);
        for (int i = 0; i < n;i++)
            for (int j = target; j >= stones[i];j--)
                dp[j] = max(dp[j], stones[i]+ dp[j - stones[i]]);
        return sum - 2 * (*max_element(dp.begin(), dp.end()));
    }
};

int main()
{
    Solution sol;
    vector<int> stones = {2,7,4,1,8,1};
    cout << sol.lastStoneWeightII(stones) << endl;
    return 0;
}