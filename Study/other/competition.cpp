#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <map>
#include <algorithm>
using namespace std;

class Solution
{
    struct TreeNode
    {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

public:
    vector<vector<int>> largestLocal(vector<vector<int>> &grid)
    {
        int n = grid.size();
        vector<vector<int>> res;
        for (int i = 0; i < n - 2; i++)
        {
            for (int x = i + 1; x < i + 4; x++)
            {
                // for(int y = ) {

                // }
            }
        }
    }

    string smallestNumber(string pattern)
    {
        vector<int> dp(10, 0);
        int n = pattern.size();
        for (int i = 0; i < n; i++)
        {
        }
    }

    int edgeScore(vector<int> &edges)
    {
        map<long, long> p;
        map<long, long>::iterator iter;
        long count = 0;
        int res = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            if (p.find(edges[i]) == p.end())
                p[edges[i]] = i;
            else
                p[edges[i]] += i;
        }
        for (iter = p.begin(); iter != p.end(); iter++)
        {
            if (iter->second > count || (iter->second == count && res > iter->first))
            {
                res = iter->first;
                count = iter->second;
            }
        }
        return res;
    }

    int countSpecialNumbers(int n)
    {
        int res = 0;
        for (int i = 1; i <= n; i++)
        {
            if (isrepeat(i))
                res++;
        }
        return res;
    }
    bool isrepeat(int n)
    {
        vector<int> dp(10, 0);

        while (n >= 10)
        {
            if (dp[n % 10] == 1)
                return false;
            dp[n % 10] = 1;
            n /= 10;
        }
        if (dp[n] == 1)
            return false;
        else
            return true;
    }

    int arithmeticTriplets(vector<int> &nums, int diff)
    {
        int i = 0, j = 1, k = 2, res = 0;
        for (; j < nums.size() - 1; j++)
        {
            for (; i < j; i++)
            {
                if (nums[k] - nums[j] == nums[j] - nums[i])
                    res++;
            }
            for (; k < nums.size(); k++)
            {
                if (nums[k] - nums[j] == nums[j] - nums[i])
                    res++;
            }
        }
    }

    int minimumRecolors(string blocks, int k)
    {
        int n = blocks.size();
        int w = 0, b = 0, max = 0;
        for (int i = 0; i < k; i++)
        {
            if (blocks[i] == 'W')
                w++;
            if (blocks[i] == 'B')
                b++;
        }
        max = b;
        for (int i = k; i < n; i++)
        {
            if (blocks[i] == 'W')
                w++;
            else
                b++;

            if (blocks[i - k] == 'W')
                w--;
            else
                b--;

            if (b >= max)
                max = b;
            if (max == k)
                return 0;
        }
        return k - max;
    }

    int secondsToRemoveOccurrences(string s)
    {
    }

    string shiftingLetters(string s, vector<vector<int>> &shifts)
    {
        // for (int i = 0; i < shifts.size(); i++)
        // {
        //     if (shifts[i][2] == 0)
        //     {
        //         for (int j = shifts[i][0]; j <= shifts[i][1]; j++)
        //         {
        //             if (s[j] == 'a')
        //                 s[j] = 'z';
        //             else
        //                 s[j]--;
        //         }
        //     }
        //     else
        //     {
        //         for (int j = shifts[i][0]; j <= shifts[i][1]; j++)
        //         {

        //             if (s[j] == 'z')
        //                 s[j] = 'a';
        //             else
        //                 s[j]++;
        //         }
        //     }
        // }
        return s;
    }

    vector<long long> maximumSegmentSum(vector<int> &nums, vector<int> &removeQueries)
    {
    }

    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int> &energy, vector<int> &experience)
    {
        int a = accumulate(energy.begin(), energy.end(), 0);
        int b = accumulate(experience.begin(), experience.end(), 0);
        int init = initialExperience;
        for (int i = 0; i < experience.size(); i++)
        {
            if (initialExperience <= experience[i])
            {
                initialExperience += experience[i] - initialExperience + 1;
            }
            initialExperience += experience[i];
        }
        int res = 0;
        if (initialEnergy <= a)
            res += a - initialEnergy + 1;

        res += initialExperience - b - init;
        return res;
    }

    int amountOfTime(TreeNode *root, int start)
    {
        map<TreeNode *, TreeNode *> parent;
        parent[root] = NULL;
        queue<TreeNode *> data;
        data.emplace(root);
        TreeNode *target;
        int res = -1;
        while (data.size() != 0)
        {
            if (data.front()->val == start)
                target = data.front();

            if (data.front()->left != NULL)
            {
                data.emplace(data.front()->left);
                parent[data.front()->left] = data.front();
            }
            if (data.front()->right != NULL)
            {
                data.emplace(data.front()->right);
                parent[data.front()->right] = data.front();
            }
            data.pop();
        }
        set<TreeNode *> tem;
        queue<TreeNode *> back;
        tem.insert(target);
        data.emplace(target);
        while (tem.size() == parent.size())
        {
            if (tem.find(data.front()->left) == tem.end())
            {
                tem.insert(data.front()->left);
                back.emplace(data.front()->left);
            }
            if (tem.find(data.front()->right) == tem.end())
            {
                tem.insert(data.front()->right);
                back.emplace(data.front()->right);
            }
            if (tem.find(parent[data.front()]) == tem.end())
            {
                tem.insert(parent[data.front()]);
                back.emplace(parent[data.front()]);
            }
            data.pop();
            if (data.empty())
            {
                res++;
                while (back.empty())
                {
                    data.emplace(back.front());
                    back.pop();
                }
            }
        }
        return res;
    }
    set<TreeNode *> tem;

    int find(map<TreeNode *, TreeNode *> parent, TreeNode *target)
    {
        tem.insert(target);

        if (target->left != NULL && tem.find(target->left) == tem.end())
            find(parent, target->left);
        if (target->right != NULL && tem.find(target->right) == tem.end())
            find(parent, target->right);
        if (parent[target] != NULL && tem.find(parent[target]) == tem.end())
            find(parent, parent[target]);
    }

    /**
     * 和有限的最长子序列
     * */

    vector<int> answerQueries(vector<int> &nums, vector<int> &queries)
    {
        sort(nums.begin(), nums.end());
        vector<int> res;
        int count, i, n = nums.size();
        for (auto query : queries)
        {
            count = 0;
            for (i = 0; i < n; i++)
            {
                count += nums[i];
                if (count > query)
                {
                    res.emplace_back(i);
                    break;
                }
            }
            if (i == n)
                res.emplace_back(i);
        }
        return res;
    }

    /**
     * 从字符串中移除星号
     * 可能*为第一个元素
     * */
    string removeStars(string s)
    {
        // string::size_type pos = s.find_first_of("*");
        // while (pos != s.npos)
        // {
        //     s.erase(pos - 1, 1);
        //     s.erase(pos - 1, 1);
        //     pos = s.find_first_of("*");
        // }
        string res;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '*') {
                res += s[i];
            } else {
                res.pop_back();
            }
        }
        return res;
    }

    /**
     *
     * 收集垃圾的最少总时间
     * */
    int garbageCollection(vector<string> &garbage, vector<int> &travel)
    {
        int n = garbage.size(), indexG = 0, indexM = 0, indexP = 0, count = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            string::size_type pos = garbage[i].find_first_of("G");
            while (pos != garbage[i].npos)
            {
                if (indexG == 0)
                    indexG = i;
                count++;
                garbage[i].erase(pos, 1);
                pos = garbage[i].find_first_of("G");
            }
            pos = garbage[i].find_first_of("M");
            while (pos != garbage[i].npos)
            {
                if (indexM == 0)
                    indexM = i;
                count++;
                garbage[i].erase(pos, 1);
                pos = garbage[i].find_first_of("M");
            }
            pos = garbage[i].find_first_of("P");
            while (pos != garbage[i].npos)
            {
                if (indexP == 0)
                    indexP = i;
                count++;
                garbage[i].erase(pos, 1);
                pos = garbage[i].find_first_of("P");
            }
        }
        count += accumulate(travel.begin(), travel.begin() + indexG, 0) + accumulate(travel.begin(), travel.begin() + indexM, 0) + accumulate(travel.begin(), travel.begin() + indexP, 0);
        return count;
    }

private:
};
int main()
{
    Solution s;
    // vector<vector<char>> dp = vector<vector<char>>(3, vector<char>(4)) = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // vector<int> dp = {1, 1, 1, 1};
    vector<string> a = {"G", "P", "GP", "GG"};
    vector<int> d = {2, 4, 3};
    cout << s.removeStars("abb*cdfg*****x*");
    // string str =
    return 0;
}
