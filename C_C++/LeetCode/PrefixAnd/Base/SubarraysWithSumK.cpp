#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/*
a[0] a[1] a[2]...a[i]...a[j]...a[n]
s[1] s[2] s[3]...s[i+1]...s[j+1]...s[n+1]

*/
class Solution
{
public:
    int subarraySum_(vector<int> &nums, int k)
    {
        int res = 0;
        auto s = vector<int>(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); i++)
            s[i] = s[i - 1] + nums[i - 1];

        for (int i = 0; i < s.size(); i++)
        {
            for (int j = i + 1; j < s.size(); j++)
            {
                if ((s[j] - s[i]) == k)
                    res++;
            }
        }
        return res;
    }
 
    int subarraySum(vector<int> &nums, int k)
    {
        int res = 0;
        auto s = vector<int>(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); i++)
            s[i] = s[i - 1] + nums[i - 1];

        unordered_map<int, int> cnt;
        for(auto sj:s)
        {
            res += cnt.count(sj - k) > 0 ? cnt[sj - k] : 0;
            cnt[sj]++;
        }
        return res;
    }
};

int main()
{
    vector<int> nums = {1, 2, 3};
    auto s = new Solution;
    cout << s->subarraySum(nums, 3);
    return 0;
}