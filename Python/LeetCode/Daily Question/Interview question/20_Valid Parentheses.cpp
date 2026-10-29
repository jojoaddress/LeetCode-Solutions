#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s)
    {
        unordered_map<char, char> mp = {{'(', ')'}, {'[', ']'}, {'{', '}'}};
        stack<char> stk;
        if(s.size()%2!=0)
            return false;

        for( auto &c:s)
        {
            if(mp.count(c))
            {
                stk.push(c);
            }
            else
            {
                if(stk.empty()||mp[stk.top()]!=c)
                    return false;
                stk.pop();
            } 
        }
        return stk.empty();
    }
};