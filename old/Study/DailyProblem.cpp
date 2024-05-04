#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <utility>
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
    vector<int> minSubsequence(vector<int> &nums)
    {
        int count = 0, i = 0, sum = accumulate(nums.begin(), nums.end(), 0);
        if (nums.size() == 1)
            return nums;
        sort(nums.rbegin(), nums.rend());

        for (i = 0; count <= sum - count; i++)
        {
            count += nums[i];
        }
        nums.erase(nums.begin() + i, nums.end());
        return nums;
    }

    TreeNode *addOneRow(TreeNode *root, int val, int depth)
    {
        // TODO:
    }

    vector<string> stringMatching(vector<string> &words)
    {
        vector<string> res;
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words.size(); j++)
            {
                if (i != j && words[j].find(words[i]) != string::npos)
                {
                    res.push_back(words[i]);
                    break;
                }
            }
        }
        return res;
    }

    vector<int> exclusiveTime(int n, vector<string> &logs)
    {
        stack<pair<int, int>> st; // {idx, 开始运行的时间}
        vector<int> res(n, 0);
        for (auto &log : logs)
        {
            char type[10];
            int idx, timestamp;
            sscanf(log.c_str(), "%d:%[^:]:%d", &idx, type, &timestamp);
            if (type[0] == 's')
            {
                if (!st.empty())
                {
                    res[st.top().first] += timestamp - st.top().second;
                    st.top().second = timestamp;
                }
                st.emplace(idx, timestamp);
            }
            else
            {
                auto t = st.top();
                st.pop();
                res[t.first] += timestamp - t.second + 1;
                if (!st.empty())
                {
                    st.top().second = timestamp + 1;
                }
            }
        }
        return res;
    }

    string makeLargestSpecial(string s)
    {
        if (s.size() <= 2)
        {
            return s;
        }
        int cnt = 0, left = 0;
        vector<string> subs;
        for (int i = 0; i < s.size(); ++i)
        {
            if (s[i] == '1')
            {
                ++cnt;
            }
            else
            {
                --cnt;
                if (cnt == 0)
                {
                    subs.push_back("1" + makeLargestSpecial(s.substr(left + 1, i - left - 1)) + "0");
                    left = i + 1;
                }
            }
        }

        sort(subs.begin(), subs.end(), greater<string>{});
        // string ans = accumulate(subs.begin(), subs.end(), ""s);
        return "";
    }

    int minStartValue(vector<int> &nums)
    {
        int min = nums[0], tem = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (tem += nums[i], tem < min)
                min = tem;
        }
        if (min > 0)
            return 1;
        return -1 * min + 1;
    }

    /**
     *  x+5-3+x=6+x-2   return    x=2
     * 通过栈将=左右两边归结为  x的系数、常数
     * x系数均为0且左右常数相等  Infinite solutions
     * x系数均为0且左右常数不相等   No solution
     * （右常数-左常数）/左x系数-右x系数
     * */
    string solveEquation(string equation)
    {
        string tem;
        tem = equation[0];
        int i, x = 0, num = 0;
        for (i = 1; i < equation.size(); i++)
        {
            if (equation[i] == '+' || equation[i] == '-' || equation[i] == '=')
            {
                if (tem[tem.size() - 1] == 'x')
                {
                    tem.erase(tem.end() - 1);
                    x += toint(tem);
                }
                else
                {
                    num -= toint(tem);
                }
                if (equation[i] == '=')
                    break;
                else
                    tem = equation[i];
            }
            else
                tem += equation[i];
        }
        if (equation[i + 1] == '+' || equation[i + 1] == '-')
            tem = equation[++i];
        else
            tem = "";
        for (++i; i < equation.size(); i++)
        {
            if (equation[i] == '+' || equation[i] == '-' || i == equation.size() - 1)
            {
                if (i == equation.size() - 1)
                    tem += equation[i];
                if (tem[tem.size() - 1] == 'x')
                {
                    tem.erase(tem.end() - 1);
                    x -= toint(tem);
                }
                else
                {
                    num += toint(tem);
                }
                tem = equation[i];
            }
            else
                tem += equation[i];
        }
        if (x == 0 && num == 0)
            return "Infinite solutions";
        if (x == 0 && num != 0)
            return "No solution";
        return "x=" + to_string(num / x);
    }

    int toint(string s)
    {
        int n = s.size();
        if (n == 0)
            return 1;
        else if (n == 1 && s[0] == '+')
            return 1;
        else if (n == 1 && s[0] == '-')
            return -1;
        else if (n > 1)
        {
            if (s[0] == '+')
            {
                s.erase(s.begin());
                return stoi(s);
            }
            else if (s[0] == '-')
            {
                s.erase(s.begin());
                return stoi(s) * -1;
            }
        }
        return stoi(s);
    }

    string reformat(string s)
    {
        int sum_digit = 0;
        for (auto &c : s)
        {
            if (isdigit(c))
            {
                sum_digit++;
            }
        }
        int sum_alpha = s.size() - sum_digit;
        if (abs(sum_digit - sum_alpha) > 1)
        {
            return "";
        }
        bool flag = sum_digit > sum_alpha;
        for (int i = 0, j = 1; i < s.size(); i += 2)
        {
            if (isdigit(s[i]) != flag)
            {
                while (isdigit(s[j]) != flag)
                {
                    j += 2;
                }
                swap(s[i], s[j]);
            }
        }
        return s;
        // string num, txt, res;
        // for (int i = 0; i < s.size(); i++)
        // {
        //     if (s[i] >= '0' && s[i] <= '9')
        //         num += s[i];
        //     else
        //         txt += s[i];
        // }
        // int tem = num.size() - txt.size();
        // if (tem == 1)
        // {
        //     res = num[0];
        //     for (int i = 0; i < txt.size(); i++)
        //     {
        //         res = res + txt[i] + num[i + 1];
        //     }
        // }
        // else if (tem == -1)
        // {
        //     res = txt[0];
        //     for (int i = 0; i < num.size(); i++)
        //     {
        //         res = res + num[i] + txt[i + 1];
        //     }
        // }
        // else if (tem == 0)
        // {
        //     res = s;
        // }
        // else
        // {
        //     res = "";
        // }
        // return res;
    }

    vector<vector<int>> groupThePeople(vector<int> &groupSizes)
    {
        vector<vector<int>> res;
        map<int, vector<int>> data;
        vector<int> tem;
        map<int, vector<int>>::iterator iter;
        for (int i = 0; i < groupSizes.size(); i++)
        {
            iter = data.find(groupSizes[i]);
            if (iter == data.end())
            {
                tem.clear();
                tem.push_back(i);
                data[groupSizes[i]] = tem;
            }
            else
            {
                if (iter->second.size() == groupSizes[i])
                {
                    res.push_back(iter->second);
                    iter->second.clear();
                    iter->second.push_back(i);
                    // data.erase(iter);
                    // tem.clear();
                    // tem.push_back(i);
                    // data[groupSizes[i]] = tem;
                }
                else
                {
                    iter->second.push_back(i);
                }
            }
        }
        for (iter = data.begin(); iter != data.end(); iter++)
        {
            res.push_back(iter->second);
        }
        return res;
    }

    int maxChunksToSorted(vector<int> &arr)
    {
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        unsigned long long xorArr = 0, xorSorted = 0;
        int res = 0;
        for (int i = 0; i < sorted.size(); i++)
        {
            xorArr += arr[i];
            xorSorted += sorted[i];
            if (xorArr == xorSorted)
                res++;
        }
        return res;
    }

    int maxScore(string s)
    {
        int score = 0;
        int n = s.size();
        if (s[0] == '0')
        {
            score++;
        }
        for (int i = 1; i < n; i++)
        {
            if (s[i] == '1')
            {
                score++;
            }
        }
        int ans = score;
        for (int i = 1; i < n - 1; i++)
        {
            if (s[i] == '0')
            {
                score++;
            }
            else
            {
                score--;
            }
            ans = max(ans, score);
        }
        return ans;
    }

    int maxlevel = -1, sum = 0;

    int deepestLeavesSum(TreeNode *root)
    {
        dfs(root, 0);
        return sum;
    }

    void dfs(TreeNode *node, int high)
    {
        if (node == nullptr)
            return;

        if (high > maxlevel)
        {
            maxlevel = high;
            sum = node->val;
        }
        else if (high == maxlevel)
            sum += node->val;

        cout << node->val;
        if (node->left != nullptr)
            dfs(node->left, high + 1);
        if (node->right != nullptr)
            dfs(node->right, high + 1);
    }

    int maxEqualFreq(vector<int> &nums)
    {
        map<int, int> data; // nums[i] ~ count
        map<int, int> flag; // count ~ counts
        map<int, int>::iterator iter;

        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            if (data.find(nums[i]) == data.end())
                data[nums[i]] = 1;
            else
                data[nums[i]]++;
        }
        for (iter = data.begin(); iter != data.end(); iter++)
        {
            if (flag.find(iter->second) == flag.end())
                flag[iter->second] = 1;
            else
                flag[iter->second]++;
        }
        for (int i = n - 1; i >= 0; i--)
        {
            if (flag.size() == 2)
            {
                int aa, ab, ba, bb;
                iter = flag.begin();
                aa = iter->first;
                ab = iter->second;
                iter++;
                ba = iter->first;
                bb = iter->second;

                if (aa > ba)
                {
                    if ((aa - 1) == ba && ab == 1)
                        return i + 1;
                    else if (ba == 1 && bb == 1)
                        return i + 1;
                }
                else
                {
                    if ((ba - 1) == aa && bb == 1)
                        return i + 1;
                    else if (aa == 1 && ab == 1)
                        return i + 1;
                }
            }
            else if (flag.size() == 1 && (flag.begin()->first == 1 || flag.begin()->second == 1))
                return i + 1;

            if (flag[data[nums[i]]] == 1)
                flag.erase(flag.find(data[nums[i]]));
            else
                flag[data[nums[i]]]--;

            if (data[nums[i]]-- > 1)
            {
                if (flag.find(data[nums[i]]) == flag.end())
                    flag[data[nums[i]]] = 1;
                else
                    flag[data[nums[i]]]++;
            }
            else
                data.erase(data.find(nums[i]));
        }
        return 1;
    }

    int busyStudent(vector<int> &startTime, vector<int> &endTime, int queryTime)
    {
        int res = 0;
        for (int i = 0; i < startTime.size(); i++)
        {
            if (queryTime >= startTime[i] && queryTime <= endTime[i])
                res++;
        }
        return res;
    }

    TreeNode *constructMaximumBinaryTree(vector<int> &nums)
    {
        if (nums.size() == 0)
            return NULL;
        if (nums.size() == 1)
        {
            TreeNode *node = new TreeNode(nums[0]);
            return node;
        }
        vector<int>::iterator max = max_element(nums.begin(), nums.end());
        TreeNode *node = new TreeNode(*max);

        vector<int> left;
        left.assign(nums.begin(), max);
        node->left = constructMaximumBinaryTree(left);
        vector<int> right;
        right.assign(max + 1, nums.end());
        node->right = constructMaximumBinaryTree(right);

        return node;
    }

    int isPrefixOfWord(string sentence, string searchWord)
    {
        stringstream ss(sentence);
        string word;
        int i = 1;
        while (ss >> word)
        {
            if (word.find(searchWord) == 0)
                return i;
            i++;
        }
        return -1;
        // int res = 1;
        // for (int i = 0; i < sentence.size(); i++)
        // {
        //     if (sentence[i] == ' ')
        //         res++;
        // }
    }

    int calDepth(TreeNode *root)
    {
        int h = 0;
        if (root->left)
        {
            h = max(h, calDepth(root->left) + 1);
        }
        if (root->right)
        {
            h = max(h, calDepth(root->right) + 1);
        }
        return h;
    }

    void dfs(vector<vector<string>> &res, TreeNode *root, int r, int c, const int &height)
    {
        res[r][c] = to_string(root->val);
        if (root->left)
        {
            dfs(res, root->left, r + 1, c - (1 << (height - r - 1)), height);
        }
        if (root->right)
        {
            dfs(res, root->right, r + 1, c + (1 << (height - r - 1)), height);
        }
    }

    vector<vector<string>> printTree(TreeNode *root)
    {
        int height = calDepth(root);
        int m = height + 1;
        int n = (1 << (height + 1)) - 1;
        vector<vector<string>> res(m, vector<string>(n, ""));
        dfs(res, root, 0, (n - 1) / 2, height);
        return res;
    }

    int getMoves(int mask, int count, int n)
    {
        int ones = __builtin_popcount(mask);
        if (n & 1)
        {
            /* 如果 n 为奇数，则每一行中 1 与 0 的数目相差为 1，且满足相邻行交替 */
            if (abs(n - 2 * ones) != 1 || abs(n - 2 * count) != 1)
            {
                return -1;
            }
            if (ones == (n >> 1))
            {
                /* 偶数位变为 1 的最小交换次数 */
                return n / 2 - __builtin_popcount(mask & 0xAAAAAAAA);
            }
            else
            {
                /* 奇数位变为 1 的最小交换次数 */
                return (n + 1) / 2 - __builtin_popcount(mask & 0x55555555);
            }
        }
        else
        {
            /* 如果 n 为偶数，则每一行中 1 与 0 的数目相等，且满足相邻行交替 */
            if (ones != (n >> 1) || count != (n >> 1))
            {
                return -1;
            }
            /* 偶数位变为 1 的最小交换次数 */
            int count0 = n / 2 - __builtin_popcount(mask & 0xAAAAAAAA);
            /* 奇数位变为 1 的最小交换次数 */
            int count1 = n / 2 - __builtin_popcount(mask & 0x55555555);
            return min(count0, count1);
        }
    }

    int movesToChessboard(vector<vector<int>> &board)
    {
        int n = board.size();
        int rowMask = 0, colMask = 0;

        /* 检查棋盘的第一行与第一列 */
        for (int i = 0; i < n; i++)
        {
            rowMask |= (board[0][i] << i);
            colMask |= (board[i][0] << i);
        }
        int reverseRowMask = ((1 << n) - 1) ^ rowMask;
        int reverseColMask = ((1 << n) - 1) ^ colMask;
        int rowCnt = 0, colCnt = 0;
        for (int i = 0; i < n; i++)
        {
            int currRowMask = 0;
            int currColMask = 0;
            for (int j = 0; j < n; j++)
            {
                currRowMask |= (board[i][j] << j);
                currColMask |= (board[j][i] << j);
            }
            /* 检测每一行的状态是否合法 */
            if (currRowMask != rowMask && currRowMask != reverseRowMask)
            {
                return -1;
            }
            else if (currRowMask == rowMask)
            {
                /* 记录与第一行相同的行数 */
                rowCnt++;
            }
            /* 检测每一列的状态是否合法 */
            if (currColMask != colMask && currColMask != reverseColMask)
            {
                return -1;
            }
            else if (currColMask == colMask)
            {
                /* 记录与第一列相同的列数 */
                colCnt++;
            }
        }
        int rowMoves = getMoves(rowMask, rowCnt, n);
        int colMoves = getMoves(colMask, colCnt, n);
        return (rowMoves == -1 || colMoves == -1) ? -1 : (rowMoves + colMoves);
    }

    bool canBeEqual(vector<int> &target, vector<int> &arr)
    {
        if (target.size() != arr.size())
            return false;
        else
        {
            sort(target.begin(), target.end());
            sort(arr.begin(), arr.end());
            for (int i = 0; i < target.size(); i++)
            {
                if (target[i] != arr[i])
                    return false;
            }
            return true;
        }
    }

    vector<int> findClosestElements(vector<int> &arr, int k, int x)
    {
        int right = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int left = right - 1;
        while (k--)
        {
            if (left < 0)
            {
                right++;
            }
            else if (right >= arr.size())
            {
                left--;
            }
            else if (x - arr[left] <= arr[right] - x)
            {
                left--;
            }
            else
            {
                right++;
            }
        }
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
    int maxProduct(vector<int> &nums)
    {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        return (nums[n - 1] * nums[n - 2]);
    }
    int widthOfBinaryTree(TreeNode *root)
    {
        vector<pair<TreeNode *, unsigned long long>> index;
        unsigned long long res = 1;
        index.emplace_back(root, 1);
        while (!index.empty())
        {
            vector<pair<TreeNode *, unsigned long long>> tem;
            for (auto s : index)
            {
                if (s.first->left)
                    tem.emplace_back(s.first->left, s.second * 2);
                if (s.first->right)
                    tem.emplace_back(s.first->right, s.second * 2 + 1);
            }
            res = max(res, index.back().second - index.front().second + 1);
            index = move(tem);
        }
        return res;
    }
    vector<int> shuffle(vector<int> &nums, int n)
    {
        vector<int> res;
        for (int i = 0; i < n; i++)
        {
            res.emplace_back(nums[i]);
            res.emplace_back(nums[n + i]);
        }
        return res;
    }

    TreeNode *insertIntoMaxTree(TreeNode *root, int val)
    {
        // deque<int> data;
        // reback(root,data,true);
        // data.emplace_back(val);
        // vector<int> nums;
        // nums.assign(data.begin(),data.end());
        // return constructMaximumBinaryTree(nums);
        if (val > root->val)
        {
            TreeNode *res = new TreeNode(val);
            res->left = root;
            return res;
        }
        else
        {
        }
    }

    bool validateStackSequences(vector<int> &pushed, vector<int> &popped)
    {
        stack<int> vir;
        int i = 0;
        while (pushed[i++] != popped[0])
        {
            vir.emplace(pushed[i]);
        }
    }

    vector<int> finalPrices(vector<int> &prices)
    {
        for (int i = 0; i < prices.size(); i++)
        {
            for (int j = i + 1; j < prices.size(); j++)
            {
                if (prices[i] >= prices[j])
                {
                    prices[i] -= prices[j];
                    break;
                }
            }
        }
        return prices;
    }

    /**
     * 赢得比赛需要的最少训练时长
     */
    int minNumberOfHours(int initialEnergy, int initialExperience, vector<int> &energy, vector<int> &experience)
    {
        int res = accumulate(energy.begin(), energy.end(), 0) - initialEnergy + 1;
        res = res >= 0 ? res : 0;
        for (int i = 0; i < experience.size(); i++)
        {
            if (initialExperience > experience[i])
                initialExperience += experience[i];
            else
            {
                res += experience[i] - initialExperience + 1;
                initialExperience = experience[i] * 2 + 1;
            }
        }
        return res;
    }

    /**
     * 给定行和列的和求可行矩阵
     */
    vector<vector<int>> restoreMatrix(vector<int> &rowSum, vector<int> &colSum)
    {
        vector<vector<int>> res(rowSum.size(), vector<int>(colSum.size(), 0));
        for (int i = 0; i < rowSum.size(); i++)
        {
            for (int j = 0; j < colSum.size(); j++)
            {
                res[i][j] = min(rowSum[i], colSum[j]);
                if (rowSum[i] < colSum[j])
                {
                    colSum[j] -= rowSum[i];
                    rowSum[i] = 0;
                }
                else
                {
                    rowSum[i] -= colSum[j];
                    colSum[j] = 0;
                }
            }
        }
        return res;
    }
};

/**
 * 使用数组，即循环队列
 *
 * */
class MyCircularDeque
{
public:
    vector<int> a; // 队尾
    vector<int> b; // 队头
    int size;
    MyCircularDeque(int k)
    {
        size = k;
    }

    bool insertFront(int value)
    {
        if (a.size() + b.size() == size)
            return false;
        b.push_back(value);
        return true;
    }

    bool insertLast(int value)
    {
        if (a.size() + b.size() == size)
            return false;
        a.push_back(value);
        return true;
    }

    bool deleteFront()
    {
        if (b.size() == 0)
        {
            if (a.size() != 0)
            {
                while (a.size() != 0)
                {
                    b.push_back(a[a.size() - 1]);
                    a.pop_back();
                }
                b.pop_back();
                return true;
            }
            else
                return false;
        }
        else
        {
            b.pop_back();
            return true;
        }
    }

    bool deleteLast()
    {
        if (a.size() == 0)
        {
            if (b.size() != 0)
            {
                while (b.size() != 0)
                {
                    a.push_back(b[b.size() - 1]);
                    b.pop_back();
                }
                a.pop_back();
                return true;
            }
            else
                return false;
        }
        else
        {
            a.pop_back();
            return true;
        }
    }

    int getFront()
    {
        if (b.size() == 0)
        {
            if (a.size() != 0)
            {
                while (a.size() != 0)
                {
                    b.push_back(a[a.size() - 1]);
                    a.pop_back();
                }
                return b[b.size() - 1];
            }
            else
                return -1;
        }
        else
            return b[b.size() - 1];
    }

    int getRear()
    {
        if (a.size() == 0)
        {
            if (b.size() != 0)
            {
                while (b.size() != 0)
                {
                    a.push_back(b[b.size() - 1]);
                    b.pop_back();
                }
                return a[a.size() - 1];
            }
            else
                return -1;
        }
        else
            return a[a.size() - 1];
    }

    bool isEmpty()
    {
        if (a.size() + b.size() == 0)
            return true;
        else
            return false;
    }

    bool isFull()
    {
        if (a.size() + b.size() == size)
            return true;
        else
            return false;
    }
};

class OrderedStream
{
public:
    int ptr = 0;
    vector<char> data;

    OrderedStream(int n)
    {
        data.resize(n * 5 + 1);
        data.assign(data.size(), 0);
    }

    vector<string> insert(int idKey, string value)
    {
        vector<string> res;
        string tem = "";
        int cur = (idKey - 1) * 5;
        for (int i = 0; i < value.size(); i++)
        {
            data[cur + i] = value[i];
        }

        if (cur == ptr)
        {
            for (int i = ptr; i < data.size(); i++)
            {
                tem += data[i];
                if ((i + 1) % 5 == 0)
                {
                    res.push_back(tem);
                    tem = "";
                    if (data[i + 1] == 0)
                    {
                        ptr = i + 1;
                        break;
                    }
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution s;
    vector<int> dp = {1, 2, 3, 4, 5};
    // map<int,int> a;
    // map<int,int>::iterator iter;
    // a[1] = 2;
    // a[3] = 4;
    // iter = a.begin();
    // int ab = iter->second;
    // iter++;
    // int bb = iter->second;
    // cout << s.findClosestElements(dp, 4, 6)[0];
    vector<int> a = {1, 1, 1, 1};
    vector<int> b = {1, 1, 1, 50};
    cout << s.minNumberOfHours(1, 1, a, b);

    return 0;
}
