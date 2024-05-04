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

    int passThePillow(int n, int time)
    {
        int res = 1;
        bool flag = true;
        while (time != 0)
        {
            if (flag)
                res++;
            else
                res--;
            if (res == n)
                flag = false;
            if (res == 1)
                flag = true;
            time--;
        }
        return res;
    }

    long long kthLargestLevelSum(TreeNode *root, int k)
    {
        // TreeNode *root = new TreeNode(5);
        // TreeNode *r1 = new TreeNode(8);
        // TreeNode *r2 = new TreeNode(9);
        // TreeNode *r11 = new TreeNode(2);
        // TreeNode *r12 = new TreeNode(1);
        // TreeNode *r21 = new TreeNode(3);
        // TreeNode *r22 = new TreeNode(7);
        // TreeNode *r111 = new TreeNode(4);
        // TreeNode *r112 = new TreeNode(6);
        // root->left = r1;
        // root->right = r2;
        // r1->left = r11;
        // r1->right = r12;
        // r2->left = r21;
        // r2->right = r22;
        // r11->left = r111;
        // r11->right = r112;

        vector<long long> dp;
        long long tem = 0;
        queue<TreeNode *> a;
        queue<TreeNode *> b;

        a.emplace(root);
        while (!a.empty())
        {
            tem += a.front()->val;
            if (a.front()->left != nullptr)
                b.emplace(a.front()->left);
            if (a.front()->right != nullptr)
                b.emplace(a.front()->right);
            a.pop();
            if (a.empty())
            {
                dp.emplace_back(tem);
                tem = 0;
                swap(a, b);
            }
        }

        if (k > dp.size())
            return -1;
        sort(dp.begin(), dp.end());
        return dp[dp.size() - k];
    }

    int findValidSplit(vector<int> &nums)
    {
        unordered_map<int, int> m;
        vector<int> dp(nums.size(), 0);
        int res = 0;

        function<void(int, int)> f = [&](int n, int k) -> void
        {
            // n是质因子   k是下标
            if (m.count(n) != 0)
                dp[m[n]] = k;
            else
                m[n] = k;
        };

        for (int i = 0; i < nums.size(); i++)
        {
            // 求每个元素的所有质因子
            int d = 2;
            while (d * d <= nums[i])
            {
                if (nums[i] % d == 0)
                {
                    while (nums[i] % d == 0)
                        nums[i] /= d;
                    // d是质因子
                    f(d, i);
                }
                d++;
            }
            // nums[i]也是质因子
            if (nums[i] > 1)
                f(nums[i], i);
        }

        for (int i = 0; i < dp.size(); i++)
        {
            if (i >= res)
                return i;
            res = max(res, dp[i]);
        }
        return -1;

        // long long a = 1;
        // long long b = 1;
        // long long ta = 1;
        // long long tb = 1;
        // vector<long long> dp(nums.size() - 1, 0);
        // for (int i = 0; i < nums.size(); i++)
        //     b *= nums[i];
        // for (int i = 0; i < dp.size(); i++)
        // {
        //     a *= nums[i];
        //     b /= nums[i];
        //     ta = a;
        //     tb = b;
        //     while (ta != tb)
        //     {
        //         if (ta > tb)
        //             ta -= tb;
        //         else
        //             tb -= ta;
        //     }
        //     if (ta == 1)
        //         return i;
        // }
        // return -1;
    }

    /**
     * 背包问题
     * 原问题：n种题目  刚好凑够target分数
     * 第n种题目  做k道
     * 子问题：n-1种题目   刚好凑够target-type[n-1][1]*k
     */
    int waysToReachTarget(int target, vector<vector<int>> &types)
    {
        int MOD = 1e9 + 7;
        vector<vector<int>> dp(types.size(), vector<int>(target + 1, -1));
        function<int(int, int)> dfs = [&](int n, int k) -> int
        {
            int res = 0;
            if (n < 0)
                return k == 0 ? 1 : 0;
            for (int j = 0; j < min(types[n][0], k / types[n][1]) + 1; j++)
            {
                if (dp[n][k - types[n][1] * j] == -1)
                    dp[n][k - types[n][1] * j] = dfs(n - 1, k - types[n][1] * j);
                res = (dp[n][k - types[n][1] * j] + res) % MOD;
            }
            return res;
        };
        return dfs(types.size() - 1, target);
    }

    // int waysToReachTarget(int target, vector<vector<int>> &types)
    // {
    //     const int MOD = 1e9 + 7;
    //     int n = types.size();
    //     vector<vector<int>> dp(n + 1, vector<int>(target + 1));
    //     dp[0][0] = 1;
    //     for (int i = 1; i <= n; i++)
    //     {
    //         int count = types[i - 1][0], marks = types[i - 1][1];
    //         for (int j = 0; j <= target; j++)
    //         {
    //             dp[i][j] = dp[i - 1][j];
    //             if (j >= marks)
    //             {
    //                 dp[i][j] = (dp[i][j] + dp[i - 1][j - marks] * count) % MOD;
    //             }
    //         }
    //     }
    //     return dp[n][target];
    // }
};

int main()
{
    Solution s;
    vector<int> a = {50, 13};
    vector<int> b = {50, 26};
    vector<int> c = {50, 39};
    vector<vector<int>> dp;
    dp.emplace_back(a);
    dp.emplace_back(b);
    dp.emplace_back(c);
    vector<int> d = {4, 7, 8, 15, 3, 5};
    cout << s.findValidSplit(d);

    return 0;
}