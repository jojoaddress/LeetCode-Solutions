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
    int minimumCardPickup(vector<int> &cards)
    {
        int n = cards.size();
        int ans = INT_MAX;
        unordered_map<int, int> cnt;
        for (int i = 0; i < n;i++)
        {
            auto it = cnt.find(cards[i]);
            if(it!=cnt.end())
            {
                int temp = i - cnt[cards[i]];
                ans = min(ans, temp);
            }
            cnt[cards[i]] = i;
        }
        return ans == INT_MAX ? -1 : ans+1;
    }
};

int main()
{
    Solution sol;
    vector<int> cards = {1,0,5,3};
    cout << sol.minimumCardPickup(cards) << endl;
    return 0;
}
