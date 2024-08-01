from typing import List
from collections import defaultdict
import time
class Solution:
    # 哈希(字典)

    # 两数之和
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i, x in enumerate(nums):
            for j in range(i + 1, len(nums)):
                if x + nums[j] == target:
                    return [i, j]

s = Solution()
b = int(time.time() * 1000)
# print(int(time.time() * 1000))
print(s.twoSum([2,7,11,15], 9))
# print(int(time.time() * 1000))
e = int(time.time() * 1000)
print(e - b)