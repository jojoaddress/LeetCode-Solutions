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
    vector<int> corpFlightBookings(vector<vector<int>> &bookings, int n)
    {
        vector<int> diff(n + 2, 0);
        for (auto &b : bookings)
        {
            int first = b[0];
            int last = b[1];
            int seat = b[2];
            diff[first] += seat;
            diff[last + 1] -= seat;
        }
        int s = 0;
        vector<int> ans;
        for (int i = 1; i <= n; i++)
        {
            s += diff[i];
            ans.push_back(s);
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> bookings = {{1, 2, 10}, {2, 3, 20}, {2, 5, 25}};
    int n = 5;
    vector<int> ans = sol.corpFlightBookings(bookings, n);
    for (int x : ans)
        cout << x << " ";
    cout << endl; // Output: 10 55 25 25 25
    return 0;
}
