
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};
class Solution
{
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        ListNode *A = headA;
        ListNode *B = headB;
        while (A != B)
        {
            A = (A != nullptr ? A->next: headB);
            B = (B != nullptr ? B->next: headA);
        }
        return A;
    }
};

void main()
{
    auto s = new Solution;
    cout<<s->getIntersectionNode()<<endl;
    return;
}