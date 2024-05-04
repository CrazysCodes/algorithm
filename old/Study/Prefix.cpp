#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <algorithm>

// 前缀和类型       子数组问题

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
     * 字母与数字
     * 字母为1 数字为-1  计算前缀和数组
     */
    vector<string> findLongestSubarray(vector<string> &array)
    {
        vector<int> dp(array.size() + 1, 0);
        unordered_map<int, int> p;
        vector<string> res;
        int max = -1, index = 0;
        for (int i = 0; i < array.size(); i++) // 得到前缀和数组
        {
            if (array[i][0] <= '9' && array[i][0] >= '0')
                dp[i + 1] = dp[i] - 1;
            else
                dp[i + 1] = dp[i] + 1;
        }
        for (int i = 0; i < dp.size(); i++) // 计算两个值相等  或同为0
        {
            if (p.count(dp[i]) == 0)
                p[dp[i]] = i;
            else
            {
                if (i - p[dp[i]] > max)
                {
                    max = i - p[dp[i]];
                    index = i;
                }
            }
        }
        if (max != -1)
            res.assign(array.begin() + p[dp[index]], array.begin() + index);
        return res;
    }

    /**
     * 和为 K 的子数组
     * 思维误区：这里的哈希表p存储的是每个前缀和出现的次数
     */
    int subarraySum(vector<int> &nums, int k)
    {
        unordered_map<int, int> p;
        p[0] = 1;
        int count = 0, res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            count += nums[i];
            if (p.count(count - k) != 0)
                res += p[count - k];
            p[count]++;
        }
        return res;
    }
    /**
     * 和可被 K 整除的子数组
     */
    int subarraysDivByK(vector<int> &nums, int k)
    {
        unordered_map<int, int> dp;
        dp[0] = 1;
        int count = 0, res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            count += nums[i];
            int tem = (count % k + k) % k;
            if (dp.count(tem) != 0)
                res += dp[tem];
            dp[tem]++;
        }
        return res;
    }

    /**
     * 使数组和能被 P 整除
     */
    int minSubarray(vector<int> &nums, int p)
    {
    }
};
int main()
{
    Solution s;
    vector<string> a = {"A", "A"};
    vector<int> b = {1};
    cout << s.subarraySum(b, 0) << endl;
    cout << "Hello, " << endl ;
    return 0;
}
