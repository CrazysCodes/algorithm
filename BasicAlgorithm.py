from typing import List
from collections import defaultdict
import time
class Solution:
    # 相向双指针

    # 两数之和(有序情况 双指针)
    def twoSum(self, numbers: List[int], target: int) -> List[int]:
        left, right = 0, len(numbers) - 1
        while left < right:
            if numbers[left] + numbers[right] == target:
                return [left + 1, right + 1]
            elif numbers[left] + numbers[right] < target:
                left += 1
            else:
                right -= 1

    # 三数之和
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        res = []
        for i in range(len(nums) - 2):
            target = nums[i]
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            left, right = i + 1, len(nums) - 1
            while left < right:
                x = nums[left] + nums[right] + nums[i]
                if x == 0:
                    res.append([nums[i], nums[left], nums[right]])
                    left += 1
                    right -= 1
                    while left < right and nums[left] == nums[left - 1]:
                        left += 1
                    while left < right and nums[right] == nums[right + 1]:
                        right -= 1
                elif x < 0:
                    left += 1
                else:
                    right -= 1
        return res

    # 四数之和
    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        res = []
        for i in range(len(nums) - 3):
            if i > 0 and nums[i] == nums[i - 1]:
                continue
            for j in range(i + 1, len(nums) - 2):
                if j > i + 1 and nums[j] == nums[j - 1]:
                    continue
                left, right = j + 1, len(nums) - 1
                while left < right:
                    x = nums[i] + nums[j] + nums[left] + nums[right]
                    if x == target:
                        res.append([nums[i], nums[j], nums[left], nums[right]])
                        left += 1
                        right -= 1
                        while left < right and nums[left] == nums[left - 1]:
                            left += 1
                        while left < right and nums[right] == nums[right + 1]:
                            right -= 1
                    elif x < target:
                        left += 1
                    else:
                        right -= 1
        return res

    # 统计和小于目标的下标对数目 TODO
    # def countPairs(self, nums: List[int], target: int) -> int:




# Test 打印耗费时间
s = Solution()
b = int(time.time() * 1000)
# print(int(time.time() * 1000))
print(s.twoSum([2,7,11,15], 9))
# print(int(time.time() * 1000))
e = int(time.time() * 1000)
print(e - b)