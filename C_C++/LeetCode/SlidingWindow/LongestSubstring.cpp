/* 2023.12.20
 * 
 * 无重复字符的最长子串
 * 给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
 *
 * 滑动窗口 
 * 
 */

#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int resMax = 0;
        int len = s.size();
        int hash[128];
        memset(hash, -1, sizeof(hash));
        int i = 0;
        if (len == 0 || len == 1)
        {
            return len;
        }
        while (i < len)
        {
            int tmpMax = 0;
            int j = i;
            for (; j < len; j++)
            {
                if (hash[(int)s[j]] != -1)
                {
                    break;
                }
                hash[(int)s[j]] = j;
            }
            tmpMax = j - i;
            resMax = max(resMax, tmpMax);
            if (j >= len)
            {
                break;
            }
            i = hash[(int)s[j]] + 1;
            memset(hash, -1, sizeof(hash));
        }
        return resMax;
    }
};

class Solution_plus
{
public:
    int lengthOfLongestSubstring(string s)
    {
        if (s.size() == 0 || s.size() == 1)
            return s.size();
        unordered_set<char> lookup;
        int left = 0;
        int right = 0;
        int res = 0;
        for (int i = 0; i < s.size(); i++)
        {
            auto it = lookup.find(s[i]);
            if (it != lookup.end())
            {
                lookup.erase(s[left]);
                left ++;
            }

            res = max(res, i - left + 1);
            lookup.insert(s[i]);
        }
        return res;
    }
};

int main()
{
    Solution_plus *s1 = new Solution_plus();
    string str = "dabcab";
    s1->lengthOfLongestSubstring(str);
    return 0;
}