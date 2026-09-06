#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    int missingMultiple(vector<int>& nums, int k) {
        unordered_set<int> uset;
        for(int num:nums)
        {
            if(num%k==0)
                uset.insert(num/k);
        }
        int miss = 1;
        while(uset.count(miss))
            miss++;
        return miss * k;
    }
};