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
    /**
     * 实际上贪心策略  是需要对题目做一定判断  与验证是否能使用得归纳/证明不同   是对题目暗含的要求解读 从而解答
     * 区间问题中，考虑左端点排序或者右端点排序
     */
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
    int vowelStrings(vector<string> &words, int left, int right)
    {
        int res = 0;
        unordered_set<char> data;
        data.emplace('a');
        data.emplace('e');
        data.emplace('i');
        data.emplace('o');
        data.emplace('u');
        for (int i = left; i <= right; i++)
        {
            if (data.count(words[i][0]) == 1 && data.count(words[i][words[i].size() - 1]) == 1)
                res++;
        }
        return res;
    }
    int maxScore(vector<int> &nums)
    { // 类贪心策略   正数在前  负数在后  达到最优化情况
        vector<int> dp;
        long long pnum = 0;
        int res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] >= 0)
                pnum += nums[i];
            else
                dp.emplace_back(nums[i]);
        }
        sort(dp.begin(), dp.end());
        reverse(dp.begin(), dp.end());
        if (pnum > 0)
        {
            res = nums.size() - dp.size();
            for (int i = 0; i < dp.size(); i++)
            {
                pnum += dp[i];
                if (pnum > 0)
                    res++;
            }
        }
        return res;
    }
    long long beautifulSubarrays(vector<int> &nums)
    { // 前缀和类型  先计算异或和数组
        long long res = 0;
        unordered_map<int, int> p;
        vector<int> dp(nums.size() + 1, 0);
        for (int i = 0; i < nums.size(); i++)
            dp[i + 1] = dp[i] ^ nums[i];
        for (int i = 0; i < dp.size(); i++)
        {
            if (p.count(dp[i]) == 0)
                p[dp[i]] = 1;
            else
            {
                res += p[dp[i]];
                p[dp[i]]++;
            }
        }
        return res;
    }
    int findMinimumTime(vector<vector<int>> &tasks)
    { // 贪心策略      把每个任务尽可能晚得进行
        sort(tasks.begin(), tasks.end(), [](const vector<int> &a, const vector<int> &b)
             { return a[1] < b[1]; });
        unordered_map<int, bool> dp;
        for (int i = 0; i < tasks.size(); i++)
        {
            for (int j = tasks[i][0]; j <= tasks[i][1]; j++)
            {
                if (dp.count(j) != 0)
                    tasks[i][2]--;
                if (tasks[i][2] == 0)
                    break;
            }
            int j = tasks[i][1];
            while (tasks[i][2] > 0)
            {
                if (dp.count(j) == 0)
                {
                    tasks[i][2]--;
                    dp[j] = true;
                }
                j--;
            }
        }
        return dp.size();
    }
};

int main()
{
    Solution s;
    vector<int> a = {1, 18, 5};
    vector<int> b = {3, 15, 1};
    vector<int> c = {1, 5, 2};
    vector<vector<int>> dp;
    dp.emplace_back(a);
    dp.emplace_back(b);
    // dp.emplace_back(c);
    // cout << s.findMinimumTime(dp);
    vector<int> d = {2, -1, 0, 1, -3, 3, -3};

    return 0;
}