#include <cstring>
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    string minWindow(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        int minLen = INT_MAX;
        string res = "";
        unordered_map<char, int> ump;
        for (int i = 0; i < m; i++)
            ump[t[i]]++;

        unordered_map<char, int> window;
        int left = 0;
        int matched = 0;
        int start = 0; // 新增：仅记录最小区间的起始位置

        for (int i = 0; i < n; i++)
        {
            if (ump.count(s[i]) > 0)
            {
                window[s[i]]++;
                if (window[s[i]] == ump[s[i]])
                    matched++;
            }

            while (matched == ump.size())
            {
                int l = i - left + 1;
                if (l < minLen)
                {
                    minLen = l;
                    start = left; // 不再频繁创建字符串，只记起始下标
                }

                if (ump.count(s[left]))
                {
                    if (window[s[left]] == ump[s[left]])
                        matched--;
                    window[s[left]]--;
                }
                left++;
            }
        }

        // 仅在最后截取一次字符串
        return minLen == INT_MAX ? "" : s.substr(start, minLen);
    }
};