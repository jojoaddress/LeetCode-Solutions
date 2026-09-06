#include <iostream>
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
    vector<int> nodesBetweenCriticalPoints(ListNode *head)
    {
        int first = -1;
        int last = -1;
        vector<int> ans = {INT_MAX, -1};
        auto pre = head;
        int i = 0;
        while (head->next)
        {
            if ((pre->val < head->val && head->val > head->next->val) || (pre->val > head->val && head->val < head->next->val))
            {
                if (first == -1)
                {
                    first = i;
                }
                else
                {
                    ans[0] = min(ans[0], i - last);
                    ans[1] = i - first;
                }
                last = i;
            }
            pre = head;
            head = head->next;
            i++;
        }
        return ans[1] == -1 ? vector<int>{-1, -1} : ans;
    }
};