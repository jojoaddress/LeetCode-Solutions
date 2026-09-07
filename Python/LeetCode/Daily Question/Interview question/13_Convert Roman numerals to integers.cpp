#include <cstring>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int romanToInt(string s)
    {
        unordered_map<char, int> val = {
            {'I', 1}, {'V', 5}, {'X', 10}, {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        int ans = 0;
        int n = s.size();
        for (int i = 0; i < n; i++)
        {
            int cur = val[s[i]];
            if (i < n - 1 && cur < val[s[i + 1]])
                ans -= cur;
            else
                ans += cur;
        }
        return ans;
    }
};