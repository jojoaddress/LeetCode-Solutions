#include <cstring>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int n = s.size();
        unordered_map<char, int> cnt;
        int maxLen = 0;
        int left = 0;
        for (int i = 0; i < n;i++)
        {
            char c = s[i];
            cnt[c]++;
            while(cnt[c]>1)
            {
                cnt[s[left]]--;
                left++;
            }
            maxLen = max(maxLen, i - left + 1);
        }
        return maxLen;
    }
};

int main()
{
    Solution s;
    string str = "abcabcbb";
    cout<<s.lengthOfLongestSubstring(str)<<endl;
    return 0;
}