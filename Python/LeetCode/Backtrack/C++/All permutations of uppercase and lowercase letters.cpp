#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<string> letterCasePermutation(string s) {
        vector<string> res;
        int n = s.size();
        auto jud = [&](char c) -> bool {
            if (c>='a'&&c<='z')
                return true;
            if (c>='A'&&c<='Z')
                return true;
            return false;
        };

        auto dfs = [&](auto &&self, string &s, int depth) -> void 
        {
            for (int i = depth; i < n;i++)
            {
                if(jud(s[i]))
                {
                    s[i]=s[i] ^ 32;
                    self(self, s, i + 1);
                    s[i]=s[i] ^ 32;
                }
            }
            res.push_back(s);
        };
        dfs(dfs, s, 0);
        return res;
    }
};

int main()
{
    Solution s;
    string str = "a1b2";
    vector<string> res = s.letterCasePermutation(str);
    for (auto i : res)
        cout << i << endl;
    return 0;
}