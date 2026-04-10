from typing import List
from collections import defaultdict


class Solution:
    def totalFruit(self, fruits: List[int]) -> int:
        maxLen = 0
        left = 0
        cnt = defaultdict(int)
        for i, f in enumerate(fruits):
            cnt[f] += 1
            while len(cnt) > 2:
                cnt[fruits[left]] -= 1
                if cnt[fruits[left]] == 0:
                    del cnt[fruits[left]]
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen


if __name__ == "__main__":
    print(Solution().totalFruit([1,2,3,2,2]))
