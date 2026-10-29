#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *rotateRight(ListNode *head, int k)
    {
        vector<int> nums;
        auto cur = head;
        while (cur)
        {
            nums.push_back(cur->val);
            cur = cur->next;
        }
        int n = nums.size();
        if (n == 0) return nullptr;
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
        ListNode *dummy = new ListNode(0);
        cur = dummy;
        for (int i = 0; i < n;i++)
        {
            cur->next = new ListNode(nums[i]);
            cur = cur->next;
        }
        return dummy->next;
    }
};