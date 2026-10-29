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
    bool isIsomorphic(string s, string t)
    {
        unordered_map<char, int> ump1;
        unordered_map<char, int> ump2;
        int m = s.size(), n = t.size();
        if (m != n)
            return false;
        for (int i = 0; i < m; i++)
        {
            if (ump1[s[i]] != ump2[t[i]])
                return false;
            ump1[s[i]] = i + 1;
            ump2[t[i]] = i + 1;
        }
        return true;
    }
};