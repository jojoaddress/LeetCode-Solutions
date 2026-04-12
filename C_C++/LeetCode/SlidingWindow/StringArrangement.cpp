#include <iostream>
#include <string.h>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    bool checkInclusion(string s2,string s1)
    {
        unordered_map<char, int> need, window;
        for (char c : s2)
            need[c]++;

        int right = 0, left = 0;
        int valid = 0;
        while (right < s1.size())
        {
            char c = s1[right];
            right++;
            if (need.count(c))
            {
                window[c]++;
                if (need[c] == window[c])
                {
                    valid++;
                }
            }

            if (valid == need.size())
            {
                return true;
            }

            while (right - left >= s2.size())
            {
                char d = s1[left];
                left++;
                if (need.count(d))
                {
                    if (need[d] == window[d])
                    {
                        valid--;
                    }
                    window[d]--;
                }
            }
        }
        return false;
    }
};

int main()
{
    Solution *s1 = new Solution();
    string s = "abcdeabcdx";
    string p = "abcdxabcde";
    cout<<s1->checkInclusion(p,s);
    return 0;
}