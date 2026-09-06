#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
public:
    bool sumGame(string num)
    {
        int n = num.size();
        int sumL = 0, sumR = 0;
        int cntL = 0, cntR = 0;
        for (int i = 0; i < n / 2; ++i)
        {
            if (num[i] == '?')
                cntL++;
            else
                sumL += num[i] - '0';
        }
        for (int i = n / 2; i < n; ++i)
        {
            if (num[i] == '?')
                cntR++;
            else
                sumR += num[i] - '0';
        }

        if ((cntL + cntR) % 2 == 1)
            return true;

        int diff = sumL - sumR;
        int cnt = cntL - cntR;

        if(cnt==0)
            return diff != 0;
        else
            return abs(diff) != 9 * abs(cnt) / 2;
    }
};