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

    def twoSum(self, nums: List[int], target: int) -> List[int]:
        index = {}
        for j, x in enumerate(nums):
            if target - x in index:
                return [index[target - x], j]
            index[x] = j

    # typing模块中的List与内置list的区别：前者是类型提示和静态类型检查（确保list中元素类型一致），后者是标准数据结构（可以包含任意类型元素）
    # 字母异位词分组
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # 单个字符串排序
        index = {}
        for s in strs:
            key = ''.join(sorted(s))     # 排序后的字符串作为key
            if key in index:
                index[key].append(s)
            else:
                index[key] = [s]

    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        d = defaultdict(list)   
        for s in strs:  
            d[''.join(sorted(s))].append(s)  # sorted(s) 相同的字符串分到同一组
        return list(d.values())

    # 最长连续序列
    def longestConsecutive(self, nums: List[int]) -> int:
        nums = set(nums) #去重
        ans = 0

        ###并查集模版：
        #此处值是离散的，使用字典
        fa = {num: num for num in nums} #储存每个节点的root，初始化为自己
        size = {num : 1 for num in nums} #储存以当前节点为root的节点数量
                                    #初始化只有自己一个节点
        def find(x):
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]
        def merge(f, to):
            f = find(f)
            to = find(to)
            if f != to :
                fa[f] = to
                size[to] += size[f]

        #遍历数组，当满足合并关系时，做merge，最后取最大值即题解
        for num in nums:
            if num + 1 in fa:
                merge(num, num+1)
        if size:
            ans = max(size.values())
        return ans

# 双指针

    # 移动零
    def moveZeroes(self, nums: List[int]) -> None:
        left = 0
        for right in range(len(nums)):
            if nums[right] != 0:
                nums[left], nums[right] = nums[right], nums[left]
                left += 1

    # 盛水最多的容器
    def maxArea(self, height: List[int]) -> int:
        left, right = 0, len(height) - 1
        max_area = 0
        while left < right:
            max_area = max(max_area, (right - left) * min(height[left], height[right]))
            if height[left] < height[right]:
                left += 1
            else:
                right -= 1
        return max_area

    # 三数之和
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums = sorted(nums)
        res = []
        for i in range(len(nums) - 2):
            if i > 0 and nums[i] == nums[i - 1]:  # 去重
                continue
            target = -nums[i]
            l, r = i + 1, len(nums) - 1
            while l < r:    # 双指针
                sum = nums[l] + nums[r]
                if sum == target:
                    res.append([nums[i], nums[l], nums[r]])
                    while l < r and nums[l] == nums[l+1]: l += 1  # 去重
                    while l < r and nums[r] == nums[r-1]: r -= 1  # 去重
                    l += 1
                    r -= 1
                elif sum < target:
                    l += 1
                else:
                    r -= 1
        return res

    # 接雨水
    # TODO: 未完成
    def trap(self, height: List[int]) -> int:
        
        return 0

# 滑动窗口

    # 无重复字符的最长子串
    def lengthOfLongestSubstring(self, s: str) -> int:
        data = {}
        left, right = 0, 0
        max_len = 0
        while right < len(s):
            if s[right] in data and data[s[right]] >= left:
                left = data[s[right]] + 1
            data[s[right]] = right
            max_len = max(max_len, right - left + 1)
            right += 1
        return max_len

    # 找到字符串中所有字母异位词
    def findAnagrams(self, s: str, p: str) -> List[int]:
        tem = sorted(p)
        res = []
        for i in range(len(s) - len(p) + 1):
            if sorted(s[i:i+len(p)]) == tem:
                res.append(i)
        return res

# 子串

    # 和为 K 的子数组(前缀和、哈希表)
    def subarraySum(self, nums: List[int], k: int) -> int:
        tmp = [0]
        res = 0
        for i in range(len(nums)):
            tmp.append(nums[i] + tmp[i])
        d = defaultdict(int)
        for s in tmp:
            res += d[s - k]
            d[s] += 1
        return res
        # 暴力做法
        # tmp = [0]
        # sum = 0
        # for i in range(len(nums)):
        #     sum += nums[i]
        #     tmp.append(sum)
        # sum = 0
        # for i in range(1, len(tmp)):
        #     for j in range(i, len(tmp)):
        #         if tmp[j] - tmp[i - 1] == k:
        #             sum += 1
        # return sum


s = Solution()
b = int(time.time() * 1000)
# print(int(time.time() * 1000))
print(s.subarraySum([1,1,1], 2))
# print(int(time.time() * 1000))
e = int(time.time() * 1000)
print(e - b)