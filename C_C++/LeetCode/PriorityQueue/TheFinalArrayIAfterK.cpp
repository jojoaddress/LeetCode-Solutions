#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
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
    vector<int> getFinalState(vector<int> &nums, int k, int multiplier)
    {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minQ;
        for (int i = 0; i < nums.size(); i++)
        {
            minQ.push({nums[i], i});
        }

        for (int i = 0; i < k; i++)
        {
            pair<int,int> num = minQ.top();
            minQ.pop();
            num.first *= multiplier;
            nums[num.second] = num.first;
            minQ.push(num);
        }
        return nums;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2,1,3,5,6};
    int k = 5;
    int multiplier = 2; // Example multiplier
    vector<int> result = sol.getFinalState(nums, k, multiplier);
    
    for (int num : result)
    {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}