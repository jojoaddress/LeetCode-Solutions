#include <algorithm>
#include <bitset>
#include <deque>
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
    string predictPartyVictory(string senate)
    {
        queue<char> q;
        unordered_map<char, int> mp;
        mp['R'] = 0;
        mp['D'] = 0;
        for (auto &s : senate)
        {
            q.push(s);
            mp[s]++;
        }

        char target = ' ';
        int target_cnt = 0;
        while (!q.empty())
        {
            if (mp['R'] == 0)
                return "Dire";
            if (mp['D'] == 0)
                return "Radiant";
            char player = q.front();
            q.pop();
            if (target_cnt > 0 && player == target)
            {
                mp[player]--;
                target_cnt--;
            }
            else
            {
                target = player == 'D' ? 'R' : 'D';
                target_cnt++;
                q.push(player);
            }
        }
        return "";
    }
};

int main()
{
    Solution sol;
    string senate = "DRDRR";
    cout << sol.predictPartyVictory(senate) << endl; // "Dire"
    senate = "DDRRR";
    cout << sol.predictPartyVictory(senate) << endl; // "Dire"
    senate = "RDD";
    cout << sol.predictPartyVictory(senate) << endl; // "Dire"
    senate = "R";
    cout << sol.predictPartyVictory(senate) << endl; // "Radiant"
    return 0;
}