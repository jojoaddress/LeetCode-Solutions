from typing import List


class Solution:
    def numOfSubarrays(self, arr: List[int], k: int, threshold: int) -> int:
        res = temp = 0
        for i, num in enumerate(arr):
            # 入
            temp += num
            left = i - k + 1
            if left < 0:
                continue
            # 更新
            if temp / k >= threshold:
                res += 1
            # 出
            temp -= arr[left]
        return res


if __name__ == "__main__":
    arr = [2, 2, 2, 2, 5, 5, 5, 8]
    k = 3
    threshold = 4
    print(Solution().numOfSubarrays(arr, k, threshold))
