import copy
from typing import List, Optional
from collections import defaultdict
import time
from collections import deque
from collections import Counter

# 146. LRU 缓存 https://leetcode.cn/problems/lru-cache/description/
class LRUCache:

    def __init__(self, capacity: int):
        return

    def get(self, key: int) -> int:
        return 0

    def put(self, key: int, value: int) -> None:
        return None

# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None

class Node:
    def __init__(self, x: int, next: 'Node' = None, random: 'Node' = None):
        self.val = int(x)
        self.next = next
        self.random = random
        
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

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
                
    # 240 搜索二维矩阵 II https://leetcode.cn/problems/search-a-2d-matrix-ii/description/
    def searchMatrix(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == target:
                    return True
                elif matrix[i][j] > target:
                    break
        return False
    
    # 240 搜索二维矩阵 II https://leetcode.cn/problems/search-a-2d-matrix-ii/description/
    def searchMatrix_elegant(self, matrix: List[List[int]], target: int) -> bool:
        m, n = len(matrix), len(matrix[0])
        i, j = 0, n - 1
        while i < m and j > -1:
            if matrix[i][j] == target:
                return True
            elif matrix[i][j] < target:
                i += 1
            else:
                j -= 1
        return False
    
    # 160 相交链表 https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        lenA, lenB = 0, 0
        pA, pB = headA, headB
        while pA:
            lenA += 1
            pA = pA.next
        while pB:
            lenB += 1
            pB = pB.next
        pA, pB = headA, headB
        if lenA > lenB:
            for _ in range(lenA - lenB):
                pA = pA.next
        else:
            for _ in range(lenB - lenA):
                pB = pB.next
        while pA and pB:
            if pA == pB:
                return pA
            pA = pA.next
            pB = pB.next
        return None
    
    # 160 相交链表 https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
    def getIntersectionNode_hash(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        pA, pB = headA, headB
        hashset = set()
        while pA:
            hashset.add(pA)
            pA = pA.next
        while pB:
            if pB in hashset:
                return pB
            pB = pB.next
        return None
        
    # 160 相交链表 https://leetcode.cn/problems/intersection-of-two-linked-lists/description/
    def getIntersectionNode_elegant(self, headA: ListNode, headB: ListNode) -> Optional[ListNode]:
        pA, pB = headA, headB
        while pA != pB:
            pA = pA.next if pA else headB
            pB = pB.next if pB else headA
        return pA
    
    # 206 反转链表 https://leetcode.cn/problems/reverse-linked-list/description/
    def reverseList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        res = None
        while head:
            temp = head.next
            head.next = res
            res = head
            head = temp
        return res
    
    # 92 反转链表 II https://leetcode.cn/problems/reverse-linked-list-ii/description/
    def reverseBetween(self, head: Optional[ListNode], left: int, right: int) -> Optional[ListNode]:
        guard = ListNode(next=head)
        p0 = guard
        for _ in range(1,left):
            p0 = p0.next
        pre, cur = p0, p0.next
        for _ in range(left, right + 1):
            nxt = cur.next
            cur.next = pre
            pre = cur
            cur = nxt
        p0.next.next = cur
        p0.next = pre
        return guard.next
    
    # 234 回文链表 https://leetcode.cn/problems/palindrome-linked-list/description/
    def isPalindrome(self, head: Optional[ListNode]) -> bool:
        data = []
        while head:
            data.append(head.val)
            head = head.next
        i, j = 0, len(data) - 1
        while i < j:
            if data[i] != data[j]:
                return False
            i += 1
            j -= 1
        return True
    
    # 141 环形链表 https://leetcode.cn/problems/linked-list-cycle/description/
    def hasCycle(self, head: Optional[ListNode]) -> bool:
        data = set()
        while head:
            if head in data:
                return True
            data.add(head)
            head = head.next
        return False
    
    # 142 环形链表 II https://leetcode.cn/problems/linked-list-cycle-ii/description/
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        data = set()
        while head:
            if head in data:
                return head
            data.add(head)
            head = head.next
        return None
    
    # 21 合并两个有序链表 https://leetcode.cn/problems/merge-two-sorted-lists/description/
    def mergeTwoLists(self, list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
        def merge(list1, list2):
            if not list1:
                return list2
            if not list2:
                return list1
            if list1.val < list2.val:
                list1.next = merge(list1.next, list2)
                return list1
            else:
                list2.next = merge(list1, list2.next)
                return list2
        return merge(list1, list2)
    
    # 2 两数相加 https://leetcode.cn/problems/add-two-numbers/description/
    def addTwoNumbers(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        a, b = 0, 0
        index = 1
        while l1:
            a = a + l1.val * index
            index *= 10
            l1 = l1.next
        index = 1
        while l2:
            b = b + l2.val * index
            index *= 10
            l2 = l2.next
        c = a + b
        res = ListNode(c % 10)
        c //= 10
        head = res
        while c:
            temp = ListNode(c % 10, None)
            head.next = temp
            head = temp
            c //= 10
        return res
    
    # 19 删除链表的倒数第 N 个结点 https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/
    def removeNthFromEnd(self, head: Optional[ListNode], n: int) -> Optional[ListNode]:
        len = 0
        p = head
        while p:
            len += 1
            p = p.next
        if n == len:
            return head.next
        p = head
        for _ in range(len - n - 1):
            p = p.next
        p.next = p.next.next
        return head
    
    # 24 两两交换链表中的节点 https://leetcode.cn/problems/swap-nodes-in-pairs/description/
    def swapPairs(self, head: Optional[ListNode]) -> Optional[ListNode]:
        p = head
        while p and p.next:
            p.val, p.next.val = p.next.val, p.val
            p = p.next.next
        return head
    
    # 25 K 个一组翻转链表 https://leetcode.cn/problems/reverse-nodes-in-k-group/description/
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        guard = ListNode(next=head)
        n, p = 0, head
        while p:
            n += 1
            p = p.next
        p0, pre, cur = guard, None, head
        while n >= k:
            n -= k
            for _ in range(k):
                nxt = cur.next
                cur.next = pre
                pre = cur
                cur = nxt
            nxt = p0.next
            p0.next.next = cur
            p0.next = pre
            p0 = nxt
        return guard.next
    
    # 138 复制带随机指针的链表 https://leetcode.cn/problems/copy-list-with-random-pointer/description/
    def copyRandomList(self, head: 'Optional[Node]') -> 'Optional[Node]':
        list = []
        data = {}
        index_map = {}
        index = 0
        p = head
        while p:
            temp = Node(p.val)
            list.append(temp)
            if index > 0:
                list[index - 1].next = temp
            index_map[p] = index
            index += 1
            p = p.next
        p = head
        while p:
            if p.random:
                data[p] = index_map[p.random]
            else:
                data[p] = -1
            p = p.next
        p = head
        while p:
            if data[p] != -1:
                list[index_map[p]].random = list[data[p]]
            p = p.next
        return list[0]
    
    # 138 复制带随机指针的链表 https://leetcode.cn/problems/copy-list-with-random-pointer/description/
    def copyRandomList_elegant(self, head: 'Optional[Node]') -> 'Optional[Node]':
        if not head:
            return None
        node_map = {}
        p = head
        while p:
            node_map[p] = Node(p.val)
            p = p.next
        p = head
        while p:
            if p.next:
                node_map[p].next = node_map[p.next]
            if p.random:
                node_map[p].random = node_map[p.random]
            p = p.next
        return node_map[head]
    
    # 148 排序链表 https://leetcode.cn/problems/sort-list/description/
    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        data = []
        p = head
        while p:
            data.append(p.val)
            p = p.next
        data.sort()
        p, i = head, 0
        while p:
            p.val = data[i]
            p = p.next
            i += 1
        return head
    
    # 23. 合并 K 个升序链表 https://leetcode.cn/problems/merge-k-sorted-lists/description/
    def mergeKLists(self, lists: List[Optional[ListNode]]) -> Optional[ListNode]:
        return None
    
# 二叉树
    # 94. 二叉树的中序遍历 https://leetcode.cn/problems/binary-tree-inorder-traversal/description/
    def inorderTraversal(self, root: Optional[TreeNode]) -> List[int]:
        if root:
            return self.inorderTraversal(root.left) + [root.val] + self.inorderTraversal(root.right)
        return []
    
    # 104. 二叉树的最大深度 https://leetcode.cn/problems/maximum-depth-of-binary-tree/description/
    def maxDepth(self, root: Optional[TreeNode]) -> int:
        if root:
            return 1 + max(self.maxDepth(root.left), self.maxDepth(root.right))
        return 0
    
    # 226. 翻转二叉树  https://leetcode.cn/problems/invert-binary-tree/description/
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if root:
            root.left, root.right = root.right, root.left
            self.invertTree(root.left)
            self.invertTree(root.right)
        return root
    
    # 101. 对称二叉树 https://leetcode.cn/problems/symmetric-tree/description/
    def isSymmetric(self, root: Optional[TreeNode]) -> bool:
        if not root:
            return True
        def is_mirror(left, right):
            if not left and not right:
                return True
            if not left or not right:
                return False
            return left.val == right.val and is_mirror(left.left, right.right) and is_mirror(left.right, right.left)
        return is_mirror(root.left, root.right)
    
    # 543. 二叉树的直径 https://leetcode.cn/problems/diameter-of-binary-tree/description/
    def diameterOfBinaryTree(self, root: Optional[TreeNode]) -> int:
        ans = 0
        def dfs(node: Optional[TreeNode]) -> int:
            if node is None:
                return -1
            l_len = dfs(node.left) + 1
            r_len = dfs(node.right) + 1
            nonlocal ans
            ans = max(ans, l_len + r_len)
            return max(l_len, r_len)
        dfs(root)
        return ans
    
    # 102. 二叉树的层序遍历 https://leetcode.cn/problems/binary-tree-level-order-traversal/description/
    def levelOrder(self, root: Optional[TreeNode]) -> List[List[int]]:
        node_queue = deque([root])
        res = []
        while node_queue:
            level_size = len(node_queue)
            level_data = []
            for _ in range(level_size):
                node = node_queue.popleft()
                if node:
                    level_data.append(node.val)
                    node_queue.append(node.left)
                    node_queue.append(node.right)
            if level_data:
                res.append(level_data)
        return res
    
    # 108. 将有序数组转换为二叉搜索树 https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/description/
    def sortedArrayToBST(self, nums: List[int]) -> Optional[TreeNode]:
        if not nums:
            return None
        n = len(nums) // 2
        return TreeNode(nums[n], self.sortedArrayToBST(nums[:n]), self.sortedArrayToBST(nums[n+1:]))
    
    # 98. 验证二叉搜索树 https://leetcode.cn/problems/validate-binary-search-tree/description/
    def isValidBST(self, root: Optional[TreeNode]) -> bool:
        def dfs(node: Optional[TreeNode]) -> List[int]:
            if not node:
                return []
            return dfs(node.left) + [node.val] + dfs(node.right)
        return dfs(root) == sorted(set(dfs(root)))
        
    # 230. 二叉搜索树中第 K 小的元素 https://leetcode.cn/problems/kth-smallest-element-in-a-bst/description/
    def kthSmallest(self, root: Optional[TreeNode], k: int) -> int:
        def dfs(node: Optional[TreeNode]) -> List[int]:
            if not node:
                return []
            return dfs(node.left) + [node.val] + dfs(node.right)
        return dfs(root)[k-1]
    
    # 199. 二叉树的右视图 https://leetcode.cn/problems/binary-tree-right-side-view/description/
    def rightSideView(self, root: Optional[TreeNode]) -> List[int]:
        q = deque([root])
        res = []
        while q:
            level_data = []
            for _ in range(len(q)):
                node = q.popleft()
                if node:
                    level_data.append(node.val)
                    q.append(node.left)
                    q.append(node.right)
            if level_data:
                res.append(level_data[-1])
        return res

if __name__ == "__main__":    
    s = Solution()
    a = [1]
    b = [2]
    print(a + b)