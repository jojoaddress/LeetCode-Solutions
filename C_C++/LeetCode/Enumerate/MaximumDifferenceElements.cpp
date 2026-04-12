#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        if(is_sorted(nums.begin(), nums.end(), greater<int>()))
        {
            return -1;
        }
        int ans = 0;
        int minNum = nums[0];
        for (int i = 1; i < nums.size();i++)
        {
            ans = max(ans, nums[i] - minNum);
            minNum = min(minNum, nums[i]);
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {9,4,3,2};
    cout << sol.maximumDifference(nums) << endl;
    return 0;
}