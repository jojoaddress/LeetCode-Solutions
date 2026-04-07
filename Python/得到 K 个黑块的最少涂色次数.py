from typing import List
import sys


class Solution:
    def minimumRecolors(self, blocks: str, k: int) -> int:
        res = sys.maxsize
        temp = 0
        for i, block in enumerate(blocks):
            temp += 1 if block == "W" else 0
            left = i - k + 1
            if left < 0:
                continue
            res = min(res, temp)
            temp -= 1 if blocks[left] == "W" else 0
        return res


if __name__ == "__main__":
    blocks = "WBBWWBBWBW"
    k = 7
    print(Solution().minimumRecolors(blocks, k))
