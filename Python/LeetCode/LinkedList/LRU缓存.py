from typing import List
from typing import Optional
from collections import defaultdict

class Node:
    __slots__='pre','next','val','key'
    def __init__(self,val:int,key:int):
        self.val = val
        self.key = key

class LRUCache:

    def __init__(self, capacity: int):
        self.dummy = Node(0,0)
        self.dummy.next = self.dummy
        self.dummy.pre = self.dummy
        self.capacity = capacity
        self.key_to_node = {}

    def remove(self,x:Node) ->None:
        x.pre.next = x.next
        x.next.pre = x.pre

    def put_front(self,x:Node) ->Node:
        x.pre = self.dummy
        x.next = self.dummy.next
        x.pre.next = x
        x.next.pre = x

    def get(self, key: int) -> int:
        if key not in self.key_to_node:
            return -1
        node = self.key_to_node[key]
        self.remove(node)
        self.put_front(node)
        return node.val

    def put(self, key: int, value: int) -> None:
        if key in self.key_to_node:
            node = self.key_to_node[key]
            node.val = value
            self.remove(node)
            self.put_front(node)
        else:
            node = Node(value,key)
            self.put_front(node)
            self.key_to_node[key] = node
            if len(self.key_to_node) > self.capacity:
                back = self.dummy.pre
                del self.key_to_node[back.key]
                self.remove(back)
        
if __name__ == "__main__":
    lRUCache = LRUCache(2)
    lRUCache.put(1, 1)  # 缓存是 {1=1}
    lRUCache.put(2, 2)  # 缓存是 {1=1, 2=2}
    print(lRUCache.get(1))  # 返回 1
    lRUCache.put(3, 3)  # 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
    print(lRUCache.get(2))  # 返回 -1 (未找到)
    lRUCache.put(4, 4)  # 该操作会使得关键字 3 作废，缓存是 {1=1, 4=4}
    print(lRUCache.get(1))  # 返回 -1 (未找到)
    print(lRUCache.get(3))  # 返回 3
    print(lRUCache.get(4))  # 返回 4