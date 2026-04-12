#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <regex>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int n = pushed.size();
        vector<int> res;
        for (int i = 0, j = 0; i < n;i++)
        {
            res.push_back(pushed[i]);
            while(!res.empty()&&res.back()==popped[j])
            {
                res.pop_back();
                j++;
            }
        }
        return res.empty();
    }
};

int main()
{
    Solution sol;
    vector<int> pushed = {1,2,3,4,5};
    vector<int> popped = {4,5,3,2,1};
    bool res = sol.validateStackSequences(pushed, popped);
    cout << (res ? "true" : "false") << endl;
    return 0;
}