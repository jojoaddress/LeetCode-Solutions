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


class Solution {
public:
    ListNode* partition(ListNode* head, int x) {
        auto dummy1 = ListNode(0);
        auto dummy2 = ListNode(0);
        auto cur1 = &dummy1;
        auto cur2 = &dummy2;
        auto cur = head;
        while(cur)
        {
            if(cur->val<x)
            {
                cur1->next = cur;
                cur1 = cur1->next;
            }
            else
            {
                cur2->next = cur;
                cur2 = cur2->next;
            }
            cur = cur->next;
        }
        cur1->next = dummy2.next;
        cur2->next = nullptr;
        return dummy1.next;
    }
};