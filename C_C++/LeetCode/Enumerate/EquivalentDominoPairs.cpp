#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int numEquivDominoPairs(vector<vector<int>> &dominoes)
    {
        int n = dominoes.size();
        unordered_map<int, int> cnt;
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            int num1 = dominoes[i][0];
            int num2 = dominoes[i][1];
            int key = num1 < num2 ? num1 * 10 + num2 : num2 * 10 + num1;
            auto it = cnt.find(key);
            if(it!=cnt.end())
                res+=cnt[key];
            cnt[key]++;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> dominoes = {{1,2},{1,2},{3,4},{1,2}};
    int res = sol.numEquivDominoPairs(dominoes);
    cout << res << endl; // Output: 3
    return 0;
}