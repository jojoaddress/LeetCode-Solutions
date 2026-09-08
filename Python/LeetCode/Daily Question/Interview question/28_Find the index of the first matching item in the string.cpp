#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution {
public:
    int strStr(string haystack, string needle) {
        int n = haystack.size();
        int m = needle.size();

        if (m == 0) return 0;
        for (int i = 0; i <= n-m;i++)
        {
            if(haystack.compare(i,m,needle)==0)
                return i;
        }
        return -1;
    }
};