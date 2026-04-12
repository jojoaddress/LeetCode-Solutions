
#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    int jump(vector<int> &nums)
    {
        int len = nums.size() - 1;
        int i = 0;
        int step = 0;
        while (i < len)
        {
            int tmpMax = 0;
            int tmpJ = 0;
            if ((nums[i] + i) >= len)
            {
                step++;          
                return step;
            }

            for (int j = i + 1; j <= nums[i] + i; j++)
            {
                if (nums[j] + j >= tmpMax)
                {
                    tmpMax = nums[j] + j;
                    tmpJ = j;
                }
            }

            if (tmpMax == 0)
            {
                return 0;
            }

            step++;
            i = tmpJ;
        }
        return step;
    }
};

int main()
{
    Solution *s = new Solution();
    vector<int> nums = {1};
    cout << s->jump(nums);
    return 0;
}