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
    long long shiftDistance(string s, string t, vector<int> &nextCost, vector<int> &previousCost)
    {
        const int num = 26;
        vector<long long> nxSum(2 * num + 1);
        vector<long long> preSum(2 * num + 1);
        for (int i = 1; i <= 2 * num; i++)
        {
            nxSum[i] = nxSum[i - 1] + nextCost[(i - 1) % num];
            preSum[i] = preSum[i - 1] + previousCost[(i - 1) % num];
        }

        long long ans = 0;
        for (int i = 0; i < s.size(); i++)
        {
            int x = s[i] - 'a';
            int y = t[i] - 'a';
            ans += min(nxSum[y < x ? y + num : y] - nxSum[x], preSum[(x < y ? x + num : x)+1] - preSum[y+1]);
        }
        return ans;
    }
};

int main()
{
    string s = "abab";
    string t = "zaba";
    vector<int> nextCost = {1,2,3,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    vector<int> previousCost = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    auto sol = new Solution;
    cout << sol->shiftDistance(s, t, nextCost, previousCost) << endl;
    return 0;
}