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
#include <deque>
using namespace std;

// 2 3 5 7 11 13 17
// 放入17
// 放入13,17
// 放入11,17,13
// 放入 7,13,11,17
// 放入 5,17，7,13,11,
// 放入 3，11，5,17，7,13
// 放入 2,13，3，11，5,17，7

class Solution
{
public:
    vector<int> deckRevealedIncreasing(vector<int> &deck)
    {
        sort(deck.begin(), deck.end());
        deque<int> list;
        int n = deck.size();
        for (int i = n - 1; i >= 0; i--)
        {
            if(!list.empty())
            {
                int temp = list.back();
                list.pop_back();
                list.push_front(temp);
            }
            list.push_front(deck[i]);
        }
        vector<int> res(list.begin(), list.end());
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> deck = {17,13,11,2,3,5,7};
    vector<int> res = sol.deckRevealedIncreasing(deck);
    for (auto c : res)
    {
        cout << c << " ";
    }
    cout << endl;
    return 0;
}