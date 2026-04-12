/*
* 2023.12.13
*
* 划分字母区间
* 给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。
* 注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
* 返回一个表示每个字符串片段的长度的列表。
* 
* 一开始想到了找到每个字母的最大所在位置，但没有深入探究，导致没有想出plus方法，可惜。
*/

#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class Solution
{
public:
    vector<int> partitionLabels(string s)
    {
        int len = s.size();
        vector<int> res;

        int i = 0;

        int count = 0;

        while (i < len)
        {
            int maxSegNum = -1;
            for (int j = i + 1; j < len; j++)
            {
                char a1 = s[j];
                char a2 = s[i];
                if (s[j] == s[i])
                {
                    if (maxSegNum < j)
                    {
                        maxSegNum = j;
                    }
                }
            }

            if (maxSegNum == -1 && i < len - 1)
            {
                i++;
                res.push_back(1);
                continue;
            }
            else if (maxSegNum == -1 && i >= len - 1)
            {
                res.push_back(len - i);
                return res;
            }

            for (int l = maxSegNum + 1; l < len; l++)
            {
                for (int m = i + 1; m < maxSegNum; m++)
                {
                    if (s[l] == s[m])
                    {
                        if (maxSegNum < l)
                        {
                            maxSegNum = l;
                        }
                    }
                }
            }

            res.push_back((maxSegNum + 1) - i);
            count = 0;
            i = maxSegNum + 1;
        }
        return res;
    }
};

class Solution_plus
{
public:
    vector<int> partitionLabels(string s)
    {
        int num[26] = {0};
        int len = s.size();
        for (int i = 0; i < len; i++)
        {
            num[s[i] - 'a'] = i;
        }

        int right = 0;
        int left = 0;
        vector<int> res;
        for (int i = 0; i < len; i++)
        {
            right = max(right,num[s[i] - 'a']);
            if(right == i)
            {
                res.push_back(right - left + 1);
                left = right+1;
            }
        }
        return res;
    }
};

int main()
{
    Solution_plus *s1 = new Solution_plus();
    string str = "ababcbacadefegdehijhklij";
    s1->partitionLabels(str);
    return 0;
}