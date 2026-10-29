#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    bool wordPattern(string pattern, string s)
    {
        vector<string> str;
        string temp;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == ' ')
            {
                str.push_back(temp);
                temp = "";
                continue;
            }
            temp += s[i];
        }
        str.push_back(temp);

        unordered_map<char, int> ump1;
        unordered_map<string, int> ump2;
        if(pattern.size()!=str.size())
            return false;
        for (int i = 0; i < pattern.size();i++)
        {
            if(ump1[pattern[i]]!=ump2[str[i]])
                return false;
            ump1[pattern[i]] = i + 1;
            ump2[str[i]] = i + 1;
        }
        return true;
    }
};