#include <algorithm>
#include <bitset>
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
    int similarPairs(vector<string> &words)
    {        
        unordered_map<bitset<26>, int> cnt;
        int ans = 0;
        for (auto w : words)
        {
            bitset<26> letter;
            for (auto c : w)
            {
                int n = c - 'a';
                letter |= (1 << n);
            }
            ans += cnt.count(letter) > 0 ? cnt[letter] : 0;
            cnt[letter]++;
        }
        return ans;
    }
};

int main()
{
    Solution sol;
    vector<string> words = {"aba","aabb","abcd","bac","aabc"};
    cout << sol.similarPairs(words) << endl;
    return 0;
}