#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) return 0;
        
        unordered_set<int> st(nums.begin(), nums.end());
        st.reserve(nums.size());  // 预分配空间，减少 rehash
        
        int maxLen = 0;
        for (int num : st) {  
            if (st.find(num - 1) == st.end()) {
                int cur = num;
                int len = 1;
                while (st.find(cur + 1) != st.end()) {
                    ++cur;
                    ++len;
                }
                maxLen = max(maxLen, len);
            }
        }
        return maxLen;
    }
};