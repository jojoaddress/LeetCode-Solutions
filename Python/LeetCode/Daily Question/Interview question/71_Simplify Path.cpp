#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
#include <stack>
#include <sstream>
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        vector<string> stk;
        istringstream ss(path);
        string s;
        while(getline(ss,s,'/'))
        {
            if(s.empty() ||s==".")
                continue;
            if(s!="..")
            {
                stk.push_back(s);
            }
            else if(!stk.empty())
            {
                stk.pop_back();
            }
        }

        string res;
        for(auto &p:stk)
        {
            res += "/";
            res += p;
        }
        return res == "" ? "/" : res;
    }
};