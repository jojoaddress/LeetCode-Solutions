#include <iostream>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

class NumArray
{
public:
    NumArray(vector<int> &nums)
    {
        res.resize(nums.size() + 1);
        for (int i = 1; i <= nums.size(); i++)
        {
            res[i] = res[i - 1] + nums[i - 1];
        }
    }

    int sumRange(int left, int right)
    {

        return res[right + 1] - res[left];
    }

private:
    vector<int> res;
};

int main()
{
    vector<int> nums = {-2, 0, 3, -5, 2, -1};
    auto s = new NumArray(nums);
    cout << s->sumRange(0, 2) << endl;
    cout << s->sumRange(2, 5) << endl;
    cout << s->sumRange(0, 5) << endl;
    return 0;
}