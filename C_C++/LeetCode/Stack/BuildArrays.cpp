#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <numeric>
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
    vector<string> buildArray(vector<int> &target, int n)
    {
        vector<string> res;
        stack<int> st;
        int k = 0;
        for (int i = 1; i <= n; i++)
        {
            st.push(i);
            res.push_back("Push");
            if (i == target.back())
                break;
            if (i != target[k])
            {
                st.pop();
                res.push_back("Pop");
            }
            else
            {
                k++;
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> target = {1, 2, 3};
    int n = 3;
    vector<string> result = sol.buildArray(target, n);

    for (const string &action : result)
    {
        cout << action << " ";
    }
    cout << endl;

    return 0;
}