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

    ListNode *reverseBetween(ListNode *head, int left, int right)
    {
        auto dummy = new ListNode(0, head);
        ListNode *pre = dummy;
        for (int i = 1; i < left;i++)
            pre = pre->next;
        ListNode *cur = pre->next;
        for (int i = 0; i < right - left;i++)
        {
            ListNode *tmp = cur->next;
            cur->next = tmp->next;
            tmp->next = pre->next;
            pre->next = tmp;
        }
        return dummy->next;
    }
};