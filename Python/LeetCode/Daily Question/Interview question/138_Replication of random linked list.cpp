#include <algorithm>
#include <iostream>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>
using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};


class Solution {
public:
    Node* copyRandomList(Node* head) {
        auto cur = head;
        while (cur)
        {
            auto pre = cur->next;
            cur->next = new Node(cur->val);
            cur->next->next = pre;
            cur = pre;
        }

        cur = head;
        while(cur)
        {
            if(cur->random)
            {
                cur->next->random = cur->random->next;
            }
            cur = cur->next->next;
        }

        auto dummy = new Node(0);
        auto tail = dummy;
        cur = head;
        while (cur)
        {
            auto copy = cur->next;
            cur->next = copy->next;
            tail->next = copy;  
            tail = tail->next;
            cur = cur->next;
        }
        return dummy->next;
    }
};