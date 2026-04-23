from typing import List
from typing import Optional
from collections import defaultdict


class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next


""" 
(a+b)%m =((a%m)+(b%m))%m
(ab)%m = ((a%m)(b%m))%m
x1 = R1%k, R1=1
x2 = R2%k = (R1*10+1)%k = ((R1%k)10+1%k)%k = (x1*10+1)%k ,R2 = R1*10+1 
"""


class Solution:
    def smallestRepunitDivByK(self, k: int) -> int:
        cnt = set()
        x = 1 % k
        while x and x not in cnt:
            cnt.add(x)
            x = (x * 10 + 1) % k
        return -1 if x else len(cnt) + 1
