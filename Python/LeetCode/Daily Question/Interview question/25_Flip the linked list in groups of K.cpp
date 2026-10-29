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
    ListNode *reverse(ListNode *head,ListNode *end)
    {
        auto cur = head;
        ListNode *pre = nullptr;
        while(cur!=end)
        {
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        return pre;
    }

    ListNode* reverseKGroup(ListNode* head, int k) {
        int cnt = 0;
        ListNode dummy(0, head);
        ListNode *pre = &dummy;
        auto cur = &dummy;
        while(cur)
        {
            if(cnt%k==0&&cnt!=0)
            {
                auto start = pre->next;
                auto nxt = cur->next;
                auto tmp = reverse(start, nxt);
                pre->next = tmp;
                start->next = nxt;
                pre = start;
                cur = pre->next;
            }
            else
            {
                cur = cur->next;
            }
            cnt++; 
        }
        return dummy.next;
    }
};