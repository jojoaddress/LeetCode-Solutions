#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
#include <bitset>
using namespace std;

class Solution
{
public:
    int countPalindromicSubsequence(string s)
    {
        int n = s.size();
        vector<int> left(26, 0);
        vector<int> right(26, 0);
        vector<bitset<26>> has(26, bitset<26>());
        for (int i = 1; i < n; i++)
            right[s[i] - 'a']++;

        for (int i = 1; i < n; i++)
        {
            right[s[i] - 'a']--;
            left[s[i - 1] - 'a']++;
            for (int j = 0; j < 26; j++)
            {
                if (right[j] > 0 && left[j] > 0)
                {
                    has[s[i] - 'a'] |= 1 << j;
                }
            }
        }

        int ans = 0;
        for (int i = 0; i < 26; i++)
            ans += has[i].count();
        return ans;
    }
};

int main()
{
    Solution sol;
    string s = "adc";
    int ans = sol.countPalindromicSubsequence(s);
    cout << ans << endl;
    return 0;
}
