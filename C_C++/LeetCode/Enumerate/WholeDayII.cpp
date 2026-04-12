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

class Solution
{
public:
    long long countCompleteDayPairs(vector<int> &hours)
    {
        int n = hours.size();
        unordered_map<long long, long long> cnt;
        long long ans = 0;
        for (int i = 0; i < n; i++)
        {
            int t = (-hours[i] % 24 + 24) % 24;
            ans += cnt.count(t) > 0 ? cnt[t] : 0;
            cnt[hours[i]%24]++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> hours = {12, 12, 30, 24, 24};
    cout << sol.countCompleteDayPairs(hours) << endl;
    return 0;
}