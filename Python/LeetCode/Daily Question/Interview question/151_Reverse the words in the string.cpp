#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int idx = 0;
        for (int i = 0; i < n;i++)
        {
            if(s[i]!=' ')
            {
                if(idx!=0)
                    s[idx++] = ' ';
                while(i<n&&s[i]!=' ')
                    s[idx++] = s[i++];
            }
        }
        s.resize(idx);
        reverse(s.begin(), s.end());

        int start = 0;
        for (int i = 0; i <= n;i++)
        {
            if(i==s.size()||s[i]==' ')
            {
                reverse(s.begin() + start, s.begin()+i);
                start = i + 1;
            }
        }
        return s;
    }
};