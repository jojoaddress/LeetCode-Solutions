#include <algorithm>
#include <iostream>
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
    vector<string> findLongestSubarray(vector<string> &array)
    {
        auto numString = [](const string &s)
        {
            if (isalpha(s[0]))
            return -1;
            else if (isdigit(s[0]))
            return 1;
            return 0;
        };
        int n = array.size();
        vector<int> s(n + 1);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + numString(array[i - 1]);

        unordered_map<int, int> cnt;
        cnt[0] = -1;
        int ans = 0;
        int right = 0;
        int left = 0;
        for (int i = 0; i <= n; i++)
        {
            auto p = cnt.find(s[i]);
            if (p != cnt.end())
            {
                if (i - p->second > ans)
                {
                    ans = i - p->second;
                    right = i;
                    left = (p->second);
                }
            }
            else
            {
                cnt[s[i]] = i;
            }
        }

        if (ans == 0) return {};
        return vector<string>(array.begin() + left, array.begin() + left + ans);
    }
};

int main()
{
    auto s = new Solution;
    vector<string> nums = {"42","10","O","t","y","p","g","B","96","H","5","v","P","52","25","96","b","L","Y","z","d","52","3","v","71","J","A","0","v","51","E","k","H","96","21","W","59","I","V","s","59","w","X","33","29","H","32","51","f","i","58","56","66","90","F","10","93","53","85","28","78","d","67","81","T","K","S","l","L","Z","j","5","R","b","44","R","h","B","30","63","z","75","60","m","61","a","5","S","Z","D","2","A","W","k","84","44","96","96","y","M"};
    auto ans = s->findLongestSubarray(nums);
    for (auto a : ans)
        cout << a << " ";
    return 0;
}