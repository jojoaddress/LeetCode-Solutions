#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> ump;
        int n = ransomNote.size();
        int m = magazine.size();
        if(n>m)
            return false;
        for (int i = 0; i < m;i++)
            ump[magazine[i]]++;
        for (int i = 0; i < n;i++)
        {
            if(ump[ransomNote[i]]>0)
                ump[ransomNote[i]]--;
            else
                return false;
        }
        return true;
    }
};