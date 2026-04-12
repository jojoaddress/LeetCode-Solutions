#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int right = 0;
        for (int i = 0; i < n;i++)
        {
            if(i>right)
                return false;
            right = max(right, i + nums[i]);
        }
        return true;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << (solution.canJump(nums) ? "True" : "False") << endl;
    return 0;
}