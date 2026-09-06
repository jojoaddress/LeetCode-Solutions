#include <cstring>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int s = 0;
        for(auto num:nums)
        {
            if(num!=val)
                nums[s++] = num;
        }
        return s;
    }
};