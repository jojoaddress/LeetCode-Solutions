#include <iostream>
using namespace std;

typedef struct Node
{
    int data;
    struct Node *next;
} *PNode;

PNode createLinkedList(int a[], int len);

void print(PNode head);

PNode getLinkedNode(PNode head,int index);

PNode addLinkedNode(PNode head,int data);

PNode editLinkedNode(PNode head,int index,int data);

PNode removeLinkedNode(PNode head,int index);

int main()
{
    int a[5] = {0, 1, 4, 2, 3};
    auto p = createLinkedList(a, 5);
    print(p);
    cout<<getLinkedNode(p,4)->data<<endl;
    addLinkedNode(p,10);
    print(p);
    editLinkedNode(p,6,3);
    print(p);
    removeLinkedNode(p,6);
    print(p);

    return 0;
}

PNode createLinkedList(int a[], int len)
{
    auto head = new Node;
    auto p = head;
    for (int i = 0; i < len; i++)
    {
        auto node = new Node;
        node->data = a[i];
        node->next = NULL;
        p->next = node;
        p = p->next;
    }
    return head;
}

void print(PNode head)
{
    auto p = head->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

PNode getLinkedNode(PNode head,int index)
{
	auto p = head;
	int cnt = 0;
	while(p!=NULL)
	{
		if(cnt==index)
		{
			return p;
		}
		p = p->next;
		cnt++;
	}
    return NULL;
}

PNode addLinkedNode(PNode head,int data)
{
	auto p = head;
	auto newNode = new Node;
	newNode->data = data;
    newNode->next = NULL;
	while(p->next!=NULL)
	{
		p = p->next;
	}
	p->next = newNode;
	return head;
}

PNode editLinkedNode(PNode head,int index,int data)
{
	auto p = head;
	int cnt=0;
	while(p!=NULL)
	{
		if(cnt == index)
		{
			p->data = data;
			return head;
		}
		p=p->next;
		cnt++;
	}
	return head;
}

PNode removeLinkedNode(PNode head,int index)
{
	auto pre = head;
	auto p = pre->next;
	int cnt=1;
	if(index == 0)
	{
		return pre->next;
	}
	while(p!=NULL)
	{
		if(cnt == index)
		{
			pre->next = p->next;
			return head;
		}
		pre = p;
		p=p->next;
		cnt++;
	}
	return head;
}