"""
大厂面试必刷题
"""

from typing import List
from typing import Optional
from collections import defaultdict
from collections import OrderedDict


class ListNode:
    __slots__ = "pre", "next", "val", "key"

    def __init__(self, val=0, key=0):
        self.val = val
        self.key = key
        self.pre = None
        self.next = None


class LRUCache_demo:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.cache:
            return -1
        self.cache.move_to_end(key, last=False)
        return self.cache[key]

    def put(self, key: int, value: int) -> None:
        self.cache[key] = value
        self.cache.move_to_end(key, False)
        if len(self.cache) > self.capacity:
            self.cache.popitem()


class LRUCache:

    def __init__(self, capacity: int):
        self.dummy = ListNode()
        self.dummy.pre = self.dummy
        self.dummy.next = self.dummy
        self.capacity = capacity
        self.key_to_node = {}

    def remove(self, x: ListNode) -> None:
        x.pre.next = x.next
        x.next.pre = x.pre

    def push_front(self, x: ListNode) -> None:
        x.pre = self.dummy
        x.next = self.dummy.next
        x.pre.next = x
        x.next.pre = x

    def get(self, key: int) -> int:
        if key not in self.key_to_node:
            return -1
        node = self.key_to_node[key]
        self.remove(node)
        self.push_front(node)
        return node.val

    def put(self, key: int, value: int) -> None:
        if key in self.key_to_node:
            node = self.key_to_node[key]
            node.val = value  # 更新值
            self.remove(node)
            self.push_front(node)
        else:
            node = ListNode(value,key)
            self.key_to_node[key] = node
            self.push_front(node)
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
