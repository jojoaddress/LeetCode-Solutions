from typing import List
from typing import Optional
from collections import defaultdict


class Solution:
    def furthestDistanceFromOrigin(self, moves: str) -> int:
        cnt = defaultdict(int)
        for move in moves:
            cnt[move] += 1
        return cnt['_'] + abs(cnt['R'] - cnt['L'])

if __name__ == "__main__":
    solution = Solution()
    moves = "L_RL__R"
    print(solution.furthestDistanceFromOrigin(moves))
