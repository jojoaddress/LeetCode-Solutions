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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        auto dummy = ListNode(0, head);
        auto right = &dummy;
        auto left = &dummy;
        for (int i = 0; i < n;i++)
            right = right->next;
        while(right->next)
        {
            left=left->next;
            right = right->next;
        }
        ListNode *nxt = left->next;
        left->next = left->next->next;
        delete nxt;
        return dummy.next;
    }
};