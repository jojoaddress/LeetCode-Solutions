#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int largestSumAfterKNegations(vector<int> &nums, int k)
    {
        priority_queue<int, vector<int>, greater<int>> minHeap;
        for (auto num : nums)
            minHeap.push(num);
        for (int i = 0; i < k; i++)
        {
            int num = minHeap.top();
            minHeap.pop();
            minHeap.push(-num);
        }
        int sum = 0;
        while (!minHeap.empty())
        {
            sum += minHeap.top();
            minHeap.pop();
        }
        return sum;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {4, 2, 3};
    int k = 1;
    cout << sol.largestSumAfterKNegations(nums, k) << endl;
    return 0;
}