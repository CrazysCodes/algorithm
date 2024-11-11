import copy
from typing import List
from collections import defaultdict
import time
from collections import deque
from collections import Counter
class Solution:
# typing模块中的List与内置list的区别：前者是类型提示和静态类型检查（确保list中元素类型一致），后者是标准数据结构（可以包含任意类型元素）
# 哈希(字典)

    # 1 两数之和(暴力)  https://leetcode.cn/problems/two-sum/description/
    def twoSum_violence(self, nums: List[int], target: int) -> List[int]:
        for i, x in enumerate(nums):
            for j in range(i + 1, len(nums)):
                if x + nums[j] == target:
                    return [i, j]
    # 1 两数之和(哈希表) https://leetcode.cn/problems/two-sum/description/
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        data = {}
        for index, num in enumerate(nums):
            if target - num in data:
                return index, data[target- num]
            data[num] = index

    # 49 字母异位词分组 https://leetcode.cn/problems/group-anagrams/description/
    def groupAnagrams(self, strs: List[str]) -> List[List[str]]:
        # 遍历strs
        data = defaultdict(list)     # defaultdict(list) ： 允许你为字典中的每个键指定一个默认值类型，这里默认值类型为list
        for str in strs:
            data[''.join(sorted(str))].append(str)
        return list(data.values())
    
    # 128 最长连续序列 https://leetcode.cn/problems/longest-consecutive-sequence/description/
    def longestConsecutive(self, nums: List[int]) -> int:
        nums = set(nums) #去重
        # 使用并查集
        # 并查集的操作有合并、查询、路径压缩等。
        # 对于本题，我们可以将数组中的元素看作一个集合，并将数组中的元素划分为若干个互不相交的子集，每个子集代表一个连续的序列，子集之间存在包含、相交、不相交的关系。
        data = {num : num for num in nums}
        size = {num : 1 for num in nums}
        def find(x):
            if data[x] != x:
                data[x] = find(data[x])
            return data[x]
        def union(x, y):
            x, y = find(x), find(y)
            if x != y:
                data[x] = y
                size[y] += size[x]
        
        for num in nums:
            if num + 1 in data:
                union(num, num+1)
        if size:
            return max(size.values())
        return 0

# 双指针

    # 283 移动零 https://leetcode.cn/problems/move-zeroes/description/
    def moveZeroes(self, nums: List[int]) -> None:
        zero = 0
        for index in range(len(nums)):
            if nums[index] != 0:
                nums[index], nums[zero] = nums[zero], nums[index]
                zero += 1    

    # 11 盛水最多的容器 https://leetcode.cn/problems/container-with-most-water/description/
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

    # 15 三数之和 https://leetcode.cn/problems/3sum/description/
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        nums.sort()
        res = []
        for i in range(len(nums) - 2):
            if i > 0 and nums[i] == nums[i - 1]:  # 去重
                continue
            left, right = i + 1, len(nums) - 1
            target = -nums[i]
            while left < right:
                sum = nums[left] + nums[right]
                if sum == target:
                    res.append([nums[i], nums[left], nums[right]])
                    while left < right and nums[left] == nums[left+1]: left += 1  # 去重
                    while left < right and nums[right] == nums[right-1]: right -= 1  # 去重
                    left += 1
                    right -= 1
                elif sum < target:
                    left += 1
                else:
                    right -= 1
        return res

    # 42 接雨水(按行计算) https://leetcode.cn/problems/trapping-rain-water/description/
    def trap_row(self, height: List[int]) -> int:
        res = 0
        for h in range(1, max(height) + 1):
            temp, index = 0, 0
            while index < len(height) and height[index] < h:
                index += 1
            for j in range(index, len(height)):
                if height[j] >= h:
                    res += temp
                    temp = 0
                else:
                    temp += 1
        return res
    # 42 接雨水(按列计算) https://leetcode.cn/problems/trapping-rain-water/description/
    def trap_column(self, height: List[int]) -> int:
        res = 0
        for i in range(1, len(height) - 1):
            max_left, max_right = 0, 0
            for j in range(i):
                max_left = max(max_left, height[j])
            for j in range(i, len(height)):
                max_right = max(max_right, height[j])
            res += max(0, min(max_left, max_right) - height[i])
        return res    
    # 42 接雨水(动态规划) https://leetcode.cn/problems/trapping-rain-water/description/
    def trap_dp(self, height: List[int]) -> int:
        res = 0
        max_left, max_right = [0] * len(height), [0] * len(height)
        max_left[0] = height[0]
        max_right[-1] = height[-1]
        for i in range(1, len(height)):
            max_left[i] = max(max_left[i-1], height[i])
        for i in range(len(height) - 2, -1, -1):
            max_right[i] = max(max_right[i+1], height[i])
            
        for i in range(1, len(height) - 1):
            max_left[i] = max(max_left[i-1], height[i-1])
            max_right[i] = max(max_right[i+1], height[i+1])
            res += max(0, min(max_left[i], max_right[i]) - height[i])
        return res    
    # 42 接雨水(双指针) https://leetcode.cn/problems/trapping-rain-water/description/
    def trap(self, height: List[int]) -> int:
        res = 0
        max_left, max_right = 0, 0
        left, right = 1, len(height) - 2
        for i in range(1, len(height) - 1):
            if height[left - 1] < height[right + 1]:
                max_left = max(max_left, height[left - 1])
                res += max(0, max_left - height[left - 1])
                left += 1
            else:
                max_right = max(max_right, height[right + 1])
                res += max(0, max_right - height[right + 1])
                right -= 1
        return res
    
# 滑动窗口

    # 3 无重复字符的最长子串 https://leetcode.cn/problems/longest-substring-without-repeating-characters/description/
    def lengthOfLongestSubstring(self, s: str) -> int:
        data = {}
        left, right = 0, 0
        max_len = 0
        for right in range(len(s)):
            if s[right] in data and data[s[right]] >= left:
                left = data[s[right]] + 1
            data[s[right]] = right
            max_len = max(max_len, right - left + 1)
        return max_len

    # 438 找到字符串中所有字母异位词 https://leetcode.cn/problems/find-all-anagrams-in-a-string/description/
    def findAnagrams(self, s: str, p: str) -> List[int]:
        tem = sorted(p)
        res = []
        for i in range(len(s) - len(p) + 1):
            if sorted(s[i:i+len(p)]) == tem:
                res.append(i)
        return res

# 子串

    # 560 和为 K 的子数组(前缀和、哈希表) https://leetcode.cn/problems/subarray-sum-equals-k/description/
    # 转换为前缀和后，再联系到双数之和
    def subarraySum(self, nums: List[int], k: int) -> int:
        data = defaultdict(int)
        data[0] = 1
        sum = 0
        res = 0
        for num in nums:
            sum += num
            if sum - k in data:
                res += data[sum - k]
            data[sum] += 1
        return res

    # 239 滑动窗口最大值(暴力) https://leetcode.cn/problems/sliding-window-maximum/description/
    def maxSlidingWindow_violence(self, nums: List[int], k: int) -> List[int]:
        q = deque(nums[:k])
        res = []
        for i in range(k, len(nums)):
            res.append(max(q))
            q.popleft()
            q.append(nums[i])
        res.append(max(q))
        return res
    # 239 滑动窗口最大值(单调队列) https://leetcode.cn/problems/sliding-window-maximum/description/
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        q = deque()
        res = []
        for i, num in enumerate(nums):
            # 入
            while q and nums[q[-1]] <= num:
                q.pop()
            q.append(i)
            # 出
            if q[0] <= i - k:
                q.popleft()
            # 记录
            if i >= k - 1:
                res.append(nums[q[0]])
        return res
    
    # 76 最小覆盖子串 https://leetcode.cn/problems/minimum-window-substring/description/
    def minWindow(self, s: str, t: str) -> str:
        ans_left, ans_right = -1, len(s)
        map_s = Counter()
        map_t = Counter(t)
        
        left = 0
        for right, c in enumerate(s):
            map_s[c] += 1
            while map_s >= map_t:
                if right - left < ans_right - ans_left:
                    ans_left, ans_right = left, right
                map_s[s[left]] -= 1
                left += 1
        return "" if ans_left < 0 else s[ans_left:ans_right + 1]

    # 普通数组
    
    # 53 最大子数组和 https://leetcode.cn/problems/maximum-subarray/description/
    def maxSubArray(self, nums: List[int]) -> int:
        data = [0] * len(nums)
        data[0] = nums[0]
        for i in range(1, len(nums)):
            data[i] = max(nums[i], data[i-1] + nums[i])
        return max(data)
    
    # 56 合并区间 https://leetcode.cn/problems/merge-intervals/description/
    def merge(self, intervals: List[List[int]]) -> List[List[int]]:
        intervals.sort(key=lambda x: x[0])
        res = []
        for interval in intervals:
            if res and interval[0] <= res[-1][1]:
                res[-1][1] = max(res[-1][1], interval[1])
            else:
                res.append(interval) 
        return res
    
    # 189 轮转数组 https://leetcode.cn/problems/rotate-array/description/
    def rotate(self, nums: List[int], k: int) -> None:
        k %= len(nums)
        nums.reverse()
        nums[:k] = nums[:k][::-1]
        nums[k:] = nums[k:][::-1]
    
    # 238 除自身以外数组的乘积 https://leetcode.cn/problems/product-of-array-except-self/description/
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        head, tail, res = [], [], []
        acc = 1
        for num in nums:
            head.append(acc)
            acc *= num
        acc = 1
        for num in reversed(nums):
            tail.append(acc)
            acc *= num
        for i in range(len(nums)):
            res.append(head[i] * tail[len(nums) - i - 1])
        return res
    
    # 238 除自身以外数组的乘积 (优化) https://leetcode.cn/problems/product-of-array-except-self/description/
    def productExceptSelf_elegant(self, nums: List[int]) -> List[int]:
        n = len(nums)
        pre = [1] * n
        for i in range(1, n):
            pre[i] = pre[i - 1] * nums[i - 1]

        suf = [1] * n
        for i in range(n - 2, -1, -1):
            suf[i] = suf[i + 1] * nums[i + 1]

        return [p * s for p, s in zip(pre, suf)]
    
    # 238 除自身以外数组的乘积 (优化) https://leetcode.cn/problems/product-of-array-except-self/description/
    def productExceptSelf_elegant2(self, nums: List[int]) -> List[int]:
        n = len(nums)
        suf = [1] * n
        for i in range(n - 2, -1, -1):
            suf[i] = suf[i + 1] * nums[i + 1]

        pre = 1
        for i, x in enumerate(nums):
            # 此时 pre 为 nums[0] 到 nums[i-1] 的乘积，直接乘到 suf[i] 中
            suf[i] *= pre
            pre *= x

        return suf

    # 41 缺失的第一个正数 https://leetcode.cn/problems/first-missing-positive/description/
    def firstMissingPositive(self, nums: List[int]) -> int:
        for i in range(len(nums)):
            while 1 <= nums[i] <= len(nums) and nums[nums[i] - 1] != nums[i]:
                nums[nums[i] - 1], nums[i] = nums[i], nums[nums[i] - 1]
        for i in range(len(nums)):
            if nums[i] != i + 1:
                return i + 1
        return len(nums) + 1
    
    # 41 缺失的第一个正数 https://leetcode.cn/problems/first-missing-positive/description/
    def firstMissingPositive(self, nums: List[int]) -> int:
        data = set(nums)
        res = 1
        for i in range(1, len(nums) + 2):
            if i not in data:
                return i
            res = i + 1
        return res
    
    # 矩阵
    
    # 73 矩阵置零 https://leetcode.cn/problems/set-matrix-zeroes/description/
    def setZeroes(self, matrix: List[List[int]]) -> None:
        row = set()
        col = set()
        for i in range(len(matrix)):
            for j in range(len(matrix[0])):
                if matrix[i][j] == 0:
                    row.add(i)
                    col.add(j)
        for r in row:
            matrix[r] = [0] * len(matrix[0])
        for c in col:
            for i in range(len(matrix)):
                matrix[i][c] = 0
                
    # 54 螺旋矩阵 https://leetcode.cn/problems/spiral-matrix/description/
    def spiralOrder(self, matrix: List[List[int]]) -> List[int]:
        direction = [[0, 1], [1, 0], [0, -1], [-1, 0]]
        res = []
        m ,n = len(matrix), len(matrix[0])
        i, j, time = 0, 0, 0
        for _ in range(m * n):
            res.append(matrix[i][j])
            matrix[i][j] = None
            
            x, y = i + direction[time][0], j + direction[time][1]
            if x == m or x < 0 or y == n or y < 0 or matrix[x][y] == None:
                time = (time + 1) % 4
            
            i += direction[time][0]
            j += direction[time][1]
        return res
    
    # 48 旋转图像 https://leetcode.cn/problems/rotate-image/description/
    def rotate(self, matrix: List[List[int]]) -> None:
        data = []
        n = len(matrix)
        for j in range(n):
            temp = []
            for i in range(n-1, -1, -1):
                temp.append(matrix[i][j])
            data.append(temp)
        for i in range(n):
            for j in range(n):
                matrix[i][j] = data[i][j]
                
    # 48 旋转图像 https://leetcode.cn/problems/rotate-image/description/
    def rotate_elegant(self, matrix: List[List[int]]) -> None:
        n = len(matrix)
        tmp = copy.deepcopy(matrix)
        for i in range(n):
            for j in range(n):
                matrix[i][j] = tmp[n-1-j][i]
                
    
if __name__ == "__main__":    
    s = Solution()
    b = int(time.time() * 1000)
    print(s.spiralOrder([[1]]))
    e = int(time.time() * 1000)
    print(e - b)