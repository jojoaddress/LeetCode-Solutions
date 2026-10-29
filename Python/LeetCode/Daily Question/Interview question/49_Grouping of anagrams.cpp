#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> ump;
        for(auto &s:strs)
        {
            string key(26, 0);
            for(auto &c:s)
            {
                key[c - 'a']++;
            }
            ump[key].push_back(s);
        }
        vector<vector<string>> ans;
        for(auto &[k,str]:ump)
        {
            ans.push_back(str);
        }
        return ans;
    }
};