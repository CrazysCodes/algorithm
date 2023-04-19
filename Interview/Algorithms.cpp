#include <iostream>
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
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

    /**
     * 二分查找
     */
    int search(vector<int> &nums, int target)
    {
        int index = nums.size() / 2, res = -1;
    }

    /**
     * 有序数组的平方
     */
    vector<int> sortedSquares(vector<int> &nums)
    {
        for (int i = 0; i < nums.size(); i++)
            nums[i] *= nums[i];
        sort(nums.begin(), nums.end());
        return nums;
    }

    /**
     * 轮转数组
     */
    void rotate(vector<int> &nums, int k)
    {
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k % nums.size());
        reverse(nums.begin() + k % nums.size(), nums.end());
        return;
    }

    /**
     * 移动零
     */
    void moveZeroes(vector<int> &nums)
    {
        vector<int> dp;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] != 0)
                dp.emplace_back(nums[i]);
        }

        for (int i = 0; i < dp.size(); i++)
            nums[i] = dp[i];

        for (int i = dp.size(); i < nums.size(); i++)
            nums[i] = 0;
        return;
    }

    /**
     * 两数之和 II - 输入有序数组
     */
    vector<int> twoSum(vector<int> &numbers, int target)
    {
        
    }
};

int main()
{
    Solution s;
    vector<int> a = {1, 2, 2, 1};
    vector<int> b = {2, 2};
    vector<int> c = {2};
    s.rotate(c, 2);

    return 0;
}