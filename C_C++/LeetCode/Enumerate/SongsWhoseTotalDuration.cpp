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
    int numPairsDivisibleBy60(vector<int> &time)
    {
        int n = time.size();
        unordered_map<int, int> cnt;
        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            int mod = (-time[i] % 60 + 60) % 60;
            ans += cnt.count(mod) > 0 ? cnt[mod] : 0;
            cnt[(time[i] % 60 + 60) % 60]++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<int> time = {60,60,60};
    cout << sol.numPairsDivisibleBy60(time) << endl;
    return 0;
}