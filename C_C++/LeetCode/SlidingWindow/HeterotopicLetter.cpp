/* 2023.12.20
 *
 * 找到字符串中所有字母异位词
 * 给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。
 * 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）。
 * 
 * 第一种方法效率低，没用用到系统的学习方法
 * 第二种利用了滑动窗口，效率提高了不少。建议以后遇到子串问题，首先考虑下滑动窗口。
 */
#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        int sLen = s.size();
        int pLen = p.size();
        int letterSize = 26;
        int hash[letterSize];
        vector<int> res;
        memset(hash, 0, sizeof(hash));
        for (int i = 0; i < pLen; i++)
        {
            hash[p[i] - 'a']++;
        }
        for (int i = 0; i <= sLen - pLen; i++)
        {
            int tmpHash[letterSize];
            bool jud = true;
            memcpy(tmpHash, hash, sizeof(hash));
            for (int j = i; j < pLen + i; j++)
            {
                tmpHash[s[j] - 'a']--;
            }
            for (int k = 0; k < letterSize; k++)
            {
                if (tmpHash[k] != 0)
                {
                    jud = false;
                    break;
                }
            }
            memset(tmpHash, 0, sizeof(tmpHash));
            if (jud)
            {
                res.push_back(i);
            }
        }
        return res;
    }
};

class Solution_plus
{
public:
    vector<int> findAnagrams(string s, string p)
    {
        unordered_map<char, int> need, window;
        for (char c : p)
            need[c]++;
        int left = 0, right = 0;
        int valid = 0;
        vector<int> res;
        while (right < s.size())
        {
            char c = s[right];
            right++;
            if (need.count(c))
            {
                window[c]++;
                if (window[c] == need[c])
                {
                    valid++;
                }
            }

            if (valid == need.size())
            {
                res.push_back(left);
            }

            while (right - left >= p.size())
            {
                char d = s[left];
                left++;
                if (need.count(d))
                {
                    if (window[d] == need[d])
                    {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution_plus *s1 = new Solution_plus();
    string s = "cbaebabacd";
    string p = "abc";
    s1->findAnagrams(s, p);
    return 0;
}