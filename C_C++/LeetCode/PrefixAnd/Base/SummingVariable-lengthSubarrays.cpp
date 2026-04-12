#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums)
    {
        vector<int> s(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); i++)
            s[i] = s[i - 1] + nums[i - 1];
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            int start = max(0, i - nums[i]);
            res += s[i + 1] - s[start];
        }
        return res;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {2, 3, 1};
    cout << s->subarraySum(nums);
    return 0;
}