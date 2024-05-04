#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class Solution
{
public:
    // int fib(int n)
    // {
    //     if (n == 0)
    //         return 0;
    //     if (n == 1)
    //         return 1;
    //     return fib(n - 1) + fib(n - 2);
    // }
    int fib(int n)
    {
        int a = 0, b = 1, tem = 0;
        for (int i = 2; i <= n; i++)
        {
            tem = a + b;
            a = b;
            b = tem;
        }
        return b;
    }

    int fib(int n, vector<int> dp)
    {
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    int numWays(int n)
    {
        if (n == 0 || n == 1)
            return 1;
        int a = 1, b = 2, tem = 0;
        for (int i = 3; i <= n; i++)
        {
            tem = (a + b) % 1000000007;
            a = b;
            b = tem;
        }
        return b;
    }

    int numWays(int n, vector<int> dp)
    {
        dp[0] = 0;
        dp[1] = 1;
        for (int i = 2; i <= n; i++)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }

    bool isMatch(string s, string p)
    {
    }

    int maxSubArray(vector<int> &nums)
    {
        int max, n = nums.size();

        if (n == 0)
            return -2147483648;
        max = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (nums[i - 1] > 0)
                nums[i] += nums[i - 1];
            max = nums[i] > max ? nums[i] : max;
        }
        return max;
    }

    int translateNum(int num)
    {
        int res = 1;
        vector<int> a;
        while (num >= 10)
        {
            a.push_back(num % 10);
            num /= 10;
        }
        a.push_back(num);

        int n = a.size();
        vector<int> dp(n, 0);
        if (n == 1)
            return res;
        else
        {
            dp[n - 1] = 1;
            if (a[n - 1] * 10 + a[n - 2] < 26)
                dp[n - 2] = 2;
            else    
                dp[n - 2] = 1;
        }
        for (int i = n - 3; i >= 0; i--)
        {
            if (a[i] + a[i + 1] * 10 < 26)
                dp[i] = dp[i + 1] + dp[i + 2];
            else
                dp[i] = dp[i + 1];
        }
        return *dp.begin();
    }

    int maxValue(vector<vector<int>> &grid)
    {
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (i - 1 >= 0 && j - 1 >= 0)
                    grid[i][j] += max(grid[i][j - 1], grid[i - 1][j]);
                else if (i - 1 >= 0 && j - 1 < 0)
                    grid[i][j] += grid[i - 1][j];
                else if (i - 1 < 0 && j - 1 >= 0)
                    grid[i][j] += grid[i][j - 1];
            }
        }
        return grid[grid.size() - 1][grid[0].size() - 1];
    }

    int lengthOfLongestSubstring(string s)
    {
    }

    int nthUglyNumber(int n)
    {
    }

    vector<double> dicesProbability(int n)
    {
    }

    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int tem;
        if (n == 0)
            return 0;
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++)
        {
            tem = prices[i] - *min_element(prices.begin(), prices.end() - n + i);
            if (tem > dp[i - 1])
                dp[i] = tem;
            else
                dp[i] = dp[i - 1];
        }
        return dp[n - 1];
    }
};
int main()
{
    Solution s;
    vector<int> dp = {7, 1, 5, 3, 6, 4};
    cout << s.translateNum(12258);
    return 0;
}
