#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

class Solution
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    /**
     * 1、两数之和
     */
    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> index;
        for (int i = 0; i < nums.size(); i++)
        {
            auto iter = index.find(target - nums[i]);
            if (iter != index.end())
            {
                return {iter->second, i};
            }
            index[nums[i]] = i;
        }
        return {};
    }

    /**
     * 2、两数相加
     */
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        int tem = 0;
        ListNode *res = new ListNode(0);
        ListNode *head = res;
        while (l1 != nullptr || l2 != nullptr)
        {
            if (l1 == nullptr)

                l1->val += l2->val + tem;
            if (l1->val >= 10)
                tem = 1;
            l1->val %= 10;
        }

        return nullptr;
    }

    /**
     * 3、无重复字符的最长子串
     * 滑动窗口（队列）
     */
    int lengthOfLongestSubstring(string s)
    {
        unordered_set<char> t;
        int res = 0, len = 0, index = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (t.count(s[i]) == 0)
            {
                len++;
                t.insert(s[i]);
            }
            else
            {
                res = max(len, res);
                while (t.count(s[i]) == 1)
                    t.erase(s[index++]);
                t.insert(s[i]);
                len = t.size();
            }
        }
        return max(len, res);

        // set<char> t;
        // int res = 0, tem = 0;
        // for (int i = 0; i < s.size(); i++)
        // {
        //     for (int j = i; j < s.size(); j++)
        //     {
        //         if (t.insert(s[j]).second == true)
        //             tem++;
        //         else
        //             break;
        //     }
        //     res = max(res, tem);
        //     tem = 0;
        //     t.clear();
        // }
        // return res;
    }

    /**
     * 4、 寻找两个正序数组的中位数
     */
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int index = nums1.size()+nums2.size();
        while (index)
        {
            
        }
        
    }

    /**
     * 5、 最长回文子串
    */
    string longestPalindrome(string s) {

    }
};

int main()
{
    Solution s;
    // cout << s.lengthOfLongestSubstring("ynyo");
    
    return 0;
}