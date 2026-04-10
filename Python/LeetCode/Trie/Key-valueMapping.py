from typing import AnyStr

class Node:
    __slots__ = "son", "value", "end"

    def __init__(self):
        self.son = {}
        self.value = 0
        self.end = False

class MapSum:

    def __init__(self):
        self.root = Node()
        self.map = {}

    def insert(self, key: str, val: int) -> None:
        cur = self.root
        delta = val
        if key in self.map:
            delta -= self.map[key]
        self.map[key] = val
        for c in key:
            if c not in cur.son:
                cur.son[c] = Node()
            cur.son[c].value += delta
            cur = cur.son[c]
        cur.end = True
        
    def sum(self, prefix: str) -> int:
        res = 0
        cur = self.root
        for c in prefix:
            if c not in cur.son:
                return 0
            cur = cur.son[c]
        return cur.value
    
if __name__ == "__main__":
    solution = MapSum()
    solution.insert("a", 3)
    print(solution.sum("ap"))  # 输出 0
    solution.insert("b", 2)
    print(solution.sum("a"))  # 输出 3