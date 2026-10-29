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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *dummy = new ListNode();
        ListNode * cur = dummy;
        int res = 0;
        while (l1||l2||res)
        {
            if (l1)
            {
                res += l1->val;
                l1 = l1->next;
            }
            if(l2)
            {
                res += l2->val;
                l2 = l2->next;
            }
            cur->next = new ListNode(res % 10);
            res /= 10;
            cur = cur->next;
        }
        return dummy->next;
    }
};