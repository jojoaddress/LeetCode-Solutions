#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution_1
{
public:
    void mergeSort(int left, int right)
    {
        if (left == right)
            return;
        int mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);

        auto tmp = vector<int>(right - left + 1, 0);
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

    vector<int> input(vector<int> num)
    {
        nums = vector<int>(num);
        mergeSort(0, nums.size() - 1);
        return nums;
    }

private:
    vector<int> nums;
};

class Solution_2
{
public:
    int mergeSort(int left, int right)
    {
        if (left == right)
            return 0;
        int mid = (left + right) / 2;
        int leftCount = mergeSort(left, mid);
        int rightCount = mergeSort(mid + 1, right);

        if(nums[mid] <= nums[mid + 1])
            return leftCount + rightCount;

        vector<int> tmp(right - left + 1, 0);
        int crossCount = 0;
        int l = left, r = mid + 1, t = 0;
        while (l <= mid && r <= right)
        {
            if (nums[l] <= nums[r])
            {
                tmp[t++] = nums[l++];
            }
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

    int input(vector<int> num)
    {
        nums = vector<int>(num);
        return mergeSort(0, nums.size() - 1);
    }

private:
    vector<int> nums;
};

int main()
{
    Solution_2 sol;
    vector<int> nums = {7, 5, 6, 4};
    int inversions = sol.input(nums);
    cout << "Number of inversions: " << inversions << endl;
    return 0;
}