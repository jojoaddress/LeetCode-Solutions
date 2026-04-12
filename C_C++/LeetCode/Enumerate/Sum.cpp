#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int n = nums.size();
        unordered_map<int, int> cnt;
        for (int i = 0; i < n;i++)
        {
            auto it = cnt.find(target - nums[i]);
            if(it!=cnt.end())
                return {cnt[target - nums[i]],i};
            cnt[nums[i]] = i;
        }
        return {};
    }
};

int main() {
    Solution sol;
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;
    vector<int> res = sol.twoSum(nums, target);
    for (int i : res) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}