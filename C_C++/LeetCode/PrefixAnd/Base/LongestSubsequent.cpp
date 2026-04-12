#include <algorithm>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// sj-si<=k,max(j-i)
class Solution
{
public:
    vector<int> answerQueries_(vector<int> &nums, vector<int> &queries)
    {
        std::sort(nums.begin(), nums.end());
        vector<long> s(nums.size() + 1, 0);
        vector<int> res;
        unordered_map<int, int> cnt;

        for (int i = 1; i <= nums.size(); i++)
            s[i] = s[i - 1] + nums[i - 1];
        for (int i = 0; i < queries.size(); i++)
        {
            int temp = 0;
            for (int j = 0; j < s.size(); j++)
            {
                for (int l = j + 1; l < s.size(); l++)
                {
                    if (s[l] - s[j] <= queries[i])
                        temp = max(l - j, temp);
                }
            }
            res.push_back(temp);
        }
        return res;
    }

    vector<int> answerQueries(vector<int> &nums, vector<int> &queries)
    {
        std::sort(nums.begin(), nums.end());
        int n = nums.size();
        int m = queries.size();
        vector<int> s(n + 1, 0);
        for (int i = 1; i <= n; i++)
            s[i] = s[i - 1] + nums[i - 1];
        vector<int> answer(m);
        for (int i = 0; i < m;i++)
            answer[i] = upper_bound(s.begin(), s.end(), queries[i]) - s.begin() - 1;
        return answer;
    }
};

int main()
{
    vector<int> nums = {4, 5, 2, 1};
    vector<int> queries = {3, 10, 21};
    auto s = new Solution;
    auto res = s->answerQueries(nums, queries);
    return 0;
}