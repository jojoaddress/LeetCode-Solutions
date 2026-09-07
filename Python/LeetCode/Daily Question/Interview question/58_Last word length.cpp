#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution
{
public:
    int lengthOfLastWord(string s)
    {
        int res = 0;
        for (int i = s.size() - 1; i >= 0; i--)
        {
            if (res > 0 && s[i] == ' ')
                break;
            if (s[i] != ' ')
                res++;
        }
        return res;
    }
};