from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class MyLinkedList:

    def __init__(self):
        self.dummy = ListNode(0)

    def get(self, index: int) -> int:
        i = 0
        cur = self.dummy.next
        while cur:
            if i==index:
                return cur.val
            cur = cur.next
            i+=1
        return -1
        

    def addAtHead(self, val: int) -> None:
        nxt = self.dummy.next
        tmp = ListNode(val, nxt)
        self.dummy.next = tmp


    def addAtTail(self, val: int) -> None:
        cur = self.dummy
        while cur.next:
            cur = cur.next
        cur.next = ListNode(val)

    def addAtIndex(self, index: int, val: int) -> None:
        i = 0
        pre = self.dummy
        for _ in range(index):
            if not pre.next:
                return
            pre = pre.next
        tmp = ListNode(val,pre.next)
        pre.next = tmp

    def deleteAtIndex(self, index: int) -> None:
        i=0
        pre = self.dummy
        cur = self.dummy.next
        while cur:
            if i == index:
                pre.next = cur.next
                return
            i+=1
            pre= cur
            cur =cur.next


if __name__ == '__main__':
    linkedList = MyLinkedList()
    linkedList.addAtHead(1)
    linkedList.addAtTail(3)
    linkedList.addAtIndex(1, 2)   #链表变为1-> 2-> 3
    print(linkedList.get(1))       #返回2
    linkedList.deleteAtIndex(1)   #现在链表是1-> 3
    print(linkedList.get(1))       #返回3
        