#include <algorithm>
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
    int numOfSubarrays(vector<int> &arr)
    {
        int n = arr.size();
        int mol = 1e9 + 7;
        vector<int> s(n + 1);
        for (int i = 1; i <= n;i++)
            s[i] = arr[i-1] + s[i - 1];

        unordered_map<int, int> cnt;
        int ans = 0;
        for (int i = 1; i <= n;i++)
        {
            if(s[i]%2==0)
            {
                ans = (ans + cnt[1]) % mol;
                cnt[0]++;
            }
            else
            {
                ans = (ans + cnt[0]) % mol;
                ans++;
                cnt[1]++;
            }
        }
        return ans;
    }
};

int main()
{
    auto s = new Solution;
    vector<int> nums = {1,2,3,4,5,6,7};
    cout << s->numOfSubarrays(nums);
    return 0;
}
