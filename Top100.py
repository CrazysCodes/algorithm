class Solution:
    # 两数之和
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        for i, x in enumerate(nums):
            for j in range(i + 1, len(nums)):
                if x + nums[j] == target:
                    return [i, j]

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        index = {}
        for j, x in enumerate(nums):
            if target - x in index:
                return [index[target - x], j]
            index[x] = j
