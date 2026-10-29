#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size()!=t.size())
            return false;
        unordered_map<char, int> ump;
        for (int i = 0; i < s.size();i++)
        {
            ump[s[i]]++;
        }
        for (int i = 0;i<t.size();i++)
        {
            ump[t[i]]--;
            if(ump[t[i]]<0)
                return false;
        }
        return true;
    }
};