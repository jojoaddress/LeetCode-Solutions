#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// s[i]+s[j]=219
class Solution
{
public:
    long long calculateScore(string s)
    {
        int n = s.size();
        unordered_map<char, vector<int>> cnt;
        long long res = 0;
        for (int i = 0; i < n; i++)
        {
            char c = s[i];
            if (!cnt[219 - c].empty())
            {
                res += i - cnt[219 - c].back();
                cnt[219 - c].pop_back();
                continue;
            }
            cnt[c].push_back(i);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    string s = "zadavyayobbgqsexaabk";
    long long res = sol.calculateScore(s);
    cout << res << endl;
    return 0;
}