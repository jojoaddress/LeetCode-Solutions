from typing import List
from collections import defaultdict


class Solution:
    def maxConsecutiveAnswers(self, answerKey: str, k: int) -> int:
        cnt = defaultdict(int)
        maxLen = 0
        left = 0
        for i, a in enumerate(answerKey):
            cnt[a] += 1
            while cnt["T"] > k and cnt["F"] > k:
                cnt[answerKey[left]] -= 1
                left += 1
            maxLen = max(maxLen, i - left + 1)
        return maxLen


if __name__ == "__main__":
    print(Solution().maxConsecutiveAnswers("TTFTTFTT", 1))
