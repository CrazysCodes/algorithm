#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> res;

        // if(nums.size() == 0)
        //     return res;

        // for (int i = 0; i < nums.size() - k + 1; i++)
        // {
        //     res.push_back(*max_element(nums.begin() + i, nums.begin() + i + k));
        // }
        // return res;
        if (nums.size() == 0 || k == 0)
            return res;
        deque<int> deque;
        // 未形成窗口
        for (int i = 0; i < k; i++)
        {
            while (!deque.empty() && *(deque.end() - 1) < nums[i])
                deque.pop_back();
            deque.push_back(nums[i]);
        }
        res.push_back(*(deque.begin()));
        // 形成窗口后
        for (int i = k; i < nums.size(); i++)
        {
            if (*(deque.begin()) == nums[i - k])
                deque.pop_front();
            while (!deque.empty() && *(deque.end() - 1) < nums[i])
                deque.pop_back();
            deque.push_back(nums[i]);
            res.push_back(*(deque.begin()));
        }
        return res;
    }

    int strToInt(string str)
    {
        string num;
        long res = 1;
        for (int i = 0; i < str.size(); i++)
        {
            if (num.size() != 0 && !isdigit(str[i]))
                break;
            else if (str[i] == ' ')
                continue;
            else if (str[i] == '-' || str[i] == '+' || isdigit(str[i]))
            {
                switch (str[i])
                {
                case '-':
                    res = -1;
                case '+':
                    i++;
                    break;
                default:
                    break;
                }
                for (i; i < str.size(); i++)
                {
                    if (!isdigit(str[i]) && num.size() == 0)
                        return 0;
                    else if (isdigit(str[i]))
                        num += str[i];
                    else
                        goto count;
                }
            }
            else if (num.size() == 0 && !isdigit(str[i]))
                return 0;
        }
        count:
        long tem = 0;
        int n = num.size();
        for (int i = 0; i < num.size(); i++)
        {
            if ((num[i] - '0') * pow(10, n - i - 1) >= INT_MAX)
            {
                if (res == 1)
                    return INT_MAX;
                else if((num[i] - '0') * pow(10, n - i - 1) * res <= INT_MIN)
                    return INT_MIN;
            }
            tem += (num[i] - '0') * pow(10, n - i - 1);
        }
        return res * tem;
    }
};
int main()
{
    Solution s;
    // vector<vector<char>> dp = vector<vector<char>>(3, vector<char>(4)) = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // vector<int> dp = {2, 3, -1, -3, 5, 3, 6, 7};
    // vector<int> res = s.maxSlidingWindow(dp, 3);
    cout << s.strToInt("2147483648");
    return 0;
}
