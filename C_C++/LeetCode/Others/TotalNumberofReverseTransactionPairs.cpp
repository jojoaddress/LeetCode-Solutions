#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
public:
    int mergeSort(int left, int right, vector<int> &record)
    {
        if (left == right)
            return 0;
        int mid = (left + right) / 2;
        int leftCount = mergeSort(left, mid, record);
        int rightCount = mergeSort(mid + 1, right, record);

        if (record[mid] <= record[mid + 1])
            return leftCount + rightCount;

        vector<int> tmp(right - left + 1);
        int crossCount = 0;
        int l = left, r = mid + 1, t = 0;
        while (l <= mid && r <= right)
        {
            if (record[l] <= record[r])
                tmp[t++] = record[l++];
            else
            {
                tmp[t++] = record[r++];
                crossCount += (mid - l + 1);
            }
        }
        while(l<=mid)
            tmp[t++] = record[l++];
        while(r<=right)
            tmp[t++] = record[r++];
        for (int i = 0; i < t;i++)
            record[left + i] = tmp[i];
        return leftCount + rightCount + crossCount;
    }
    int reversePairs(vector<int> &record)
    {
        if(record.size() == 0)
            return 0;
        return mergeSort(0, record.size() - 1, record);
    }
};

int main()
{
    Solution sol;
    vector<int> record = {};
    int result = sol.reversePairs(record);
    cout << "Total number of reverse transaction pairs: " << result << endl;
    return 0;
}