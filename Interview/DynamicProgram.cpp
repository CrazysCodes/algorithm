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

    // int rob(vector<int> &nums)
    // {
    //     vector<int> dp(nums.size(), -1);
    //     function<int(int)> dfs = [&](int n) -> int
    //     {
    //         if (n == 0)
    //             return nums[0];
    //         if (n == 1)
    //             return max(nums[0], nums[1]);
    //         if (dp[n] != -1)
    //             return dp[n];
    //         return dp[n] = max(dfs(n - 1), nums[n] + dfs(n - 2));
    //     };
    //     return dfs(nums.size() - 1);
    // }
    /**
     * 打家劫舍
     */
    int rob(vector<int> &nums)
    {
        int n = nums.size(), a = 0, b = 0, res = 0;
        if (n == 1)
            return nums[0];
        if (n == 2)
            return max(nums[0], nums[1]);
        a = nums[0];
        b = max(nums[0], nums[1]);
        for (int i = 2; i < n; i++)
        {
            res = max(b, a + nums[i]);
            a = b;
            b = res;
        }
        return res;
    }
    /**
     * 打家劫舍Ⅱ（环形）
     */
    int robⅡ(vector<int> &nums)
    {
        if (nums.size() < 3)
            return rob(nums);
        int tem = nums[0];
        nums.erase(nums.begin(), nums.begin() + 1);
        int a = rob(nums);
        nums.erase(nums.begin(), nums.begin() + 1);
        nums.erase(nums.end() - 1, nums.end());
        int b = rob(nums);
        return max(a, b + tem);
    }
};

int main()
{
    Solution s;
    vector<int> a = {1, 2, 2, 1};
    vector<int> b = {2, 2};
    vector<int> c = {2};
    vector<int> d = {114, 117, 207, 117, 235, 82, 90, 67, 143, 146, 53, 108, 200, 91, 80, 223, 58, 170, 110, 236, 81, 90, 222, 160, 165, 195, 187, 199, 114, 235, 197, 187, 69, 129, 64, 214, 228, 78, 188, 67, 205, 94, 205, 169, 241, 202, 144, 240};
    cout << s.rob(d);

    return 0;
}