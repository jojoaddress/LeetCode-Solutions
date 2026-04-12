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

// RDRDDR
// 以D为例，D前面只有两种情况，数量上D>=R或者D<R
// 如果前面数量上是D>=R，D可以加到队尾
// 如果前面数量上是D<R, D需要加到队头，填线
class Solution
{
public:
    string predictPartyVictory_(string senate)
    {
        deque<char> deq;
        int R = 0, D = 0;
        for (auto &c : senate)
        {
            if (c == 'R')
            {
                if (R >= D)
                    deq.push_back(c);
                else
                    deq.push_front(c);
                R++;
            }
            else
            {
                if (D >= R)
                    deq.push_back(c);
                else
                    deq.push_front(c);
                D++;
            }
        }
        string res = deq.back() == 'D' ? "Dire" : "Radiant";
        return res;
    }

    string predictPartyVictory(string senate)
    {
        queue<char> q;
        unordered_map<char, int> mp;
        mp['R'] = 0;
        mp['D'] = 0;

        for (auto &c : senate)
        {
            q.push(c);
            mp[c]++;
        }

        char target = ' ';
        int target_count = 0;
        while (!q.empty())
        {
            if (mp['R'] == 0)
                return "Dire";
            if (mp['D'] == 0)
                return "Radiant";

            char player = q.front();
            q.pop();
            if (target_count > 0 && player == target)
            {
                target_count--;
                mp[player]--;
            }
            else
            {
                target_count++;
                target = player == 'D' ? 'R' : 'D';
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