#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
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
    int countBeautifulPairs(vector<int> &nums)
    {
        int n = nums.size();
        int ans = 0, cnt[10]{};
        for (auto x : nums)
        {
            for (int y = 1; y < 10; y++)
            {
                if (cnt[y] && std::gcd(y, x % 10) == 1)
                {
                    ans += cnt[y];
                }
            }
            while (x >= 10)
                x /= 10;
            cnt[x]++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2,5,1,4};
    cout << sol.countBeautifulPairs(nums) << endl;
    return 0;
}