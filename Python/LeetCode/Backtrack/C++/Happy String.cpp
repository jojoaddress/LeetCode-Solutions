#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    string getHappyString(int n, int k) {
        vector<string> res;
        string path = "";
        string s = "abc";

        auto dfs = [&](this auto &&dfs, int start)
        {
            if(path.size()==n)
            {
                res.push_back(path);
                return;
            }
            if(res.size()>=k)
                return;
            for (int i = 0; i < s.size();i++)
            {
                if(!path.empty()&&path.back()==s[i])
                    continue;
                path.push_back(s[i]);
                dfs(start + 1);
                path.pop_back();
            }
        };
        dfs(0);
        return res.size() >= k ? res[k - 1] : "";
    }
};

int main()
{
    Solution s;
    int n = 3, k = 9;
    string res = s.getHappyString(n, k);
    cout << res << endl;
    return 0;
}