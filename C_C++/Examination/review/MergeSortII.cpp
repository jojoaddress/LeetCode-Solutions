#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    void mergeSort2(int left, int right, vector<int> &nums)
    {
        if (left == right)
            return;
        int mid = (left + right) / 2;
        mergeSort(left, mid, nums);
        mergeSort(mid + 1, right, nums);
        vector<int> tmp(right - left + 1);
        int l = left, r = mid + 1, t = 0;

        while (l <= mid && r <= right)
        {
            if (nums[l] < nums[r])
                tmp[t++] = nums[l++];
            else
                tmp[t++] = nums[r++];
        }
        while (l <= mid)
            tmp[t++] = nums[l++];
        while (r <= right)
            tmp[t++] = nums[r++];

        for (int i = 0; i < t; i++)
            nums[left + i] = tmp[i];
    }

    void input(vector<int> &nums)
    {
        mergeSort2(0, nums.size() - 1, nums);
    }

    int mergeSort(int left, int right, vector<int> &nums)
    {
        if (left == right)
            return 0;
        int mid = (left + right) / 2;
        int leftCount = mergeSort(left, mid, nums);
        int rightCount = mergeSort(mid + 1, right, nums);
        if (nums[mid] <= nums[mid + 1])
            return leftCount + rightCount;

        int l = left, r = mid + 1, t = 0;
        int crossCount = 0;
        vector<int> tmp(right - left + 1, 0);
        while (l <= mid && r <= right)
        {
            if (nums[l] <= nums[r])
                tmp[t++] = nums[l++];
            else
            {
                tmp[t++] = nums[r++];
                crossCount += (mid - l + 1);
            }
        }
        while (l <= mid)
            tmp[t++] = nums[l++];
        while (r <= right)
            tmp[t++] = nums[r++];
        for (int i = 0; i < t; i++)
            nums[left + i] = tmp[i];
        return leftCount + rightCount + crossCount;
    }
    int reversePairs(vector<int> &record)
    {
        if (record.size() <= 1)
            return 0;
        return mergeSort(0, record.size() - 1, record);
    }
};

int main()
{
    Solution s;
    vector<int> nums = {9, 7, 5, 4, 6};
    cout << s.reversePairs(nums);
    return 0;
}