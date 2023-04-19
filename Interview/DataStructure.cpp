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

    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode(int x) : val(x), next(NULL) {}
    };

    /**
     * 存在重复元素
     */
    bool containsDuplicate(vector<int> &nums)
    {
        unordered_set<int> a;
        for (auto i : nums)
        {
            if (a.insert(i).second == false)
                return true;
        }
        return false;
    }

    /**
     * 最大子数组和（暴力会超时  要用动规）
     */
    int maxSubArray(vector<int> &nums)
    {
        vector<int> dp(nums.size(), 0);
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); i++)
        {
            if (dp[i - 1] <= 0)
                dp[i] = nums[i];
            else
                dp[i] = dp[i - 1] + nums[i];
        }
        int res = dp[0];
        for (int i = 1; i < nums.size(); i++)
            res = max(dp[i], res);

        // int res = INT32_MIN, sum = 0;
        // for (int i = 0; i < nums.size(); i++)
        // {
        //     for (int j = i; j < nums.size(); j++)
        //     {
        //         sum += nums[j];
        //         res = sum > res ? sum : res;
        //     }
        //     sum = 0;
        // }

        return res;
    }

    /**
     * 两数之和
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
     * 合并两个有序数组
     */
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        vector<int> dp(n + m, 0);
        int i = 0, j = 0, k = 0;
        while (i != m && j != n)
            dp[k++] = nums1[i] < nums2[j] ? nums1[i++] : nums2[j++];

        if (i == m)
        {
            while (j != n)
                dp[k++] = nums2[j++];
        }
        if (j == n)
        {
            while (i != m)
                dp[k++] = nums1[i++];
        }

        for (int l = 0; l < n + m; l++)
            nums1[l] = dp[l];
        return;
    }

    /**
     * 两个数组的交集 II
     */
    vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
    {
        vector<int> dp1(1001, 0);
        vector<int> dp2(1001, 0);
        vector<int> res;
        for (auto i : nums1)
            dp1[i]++;
        for (auto i : nums2)
            dp2[i]++;

        for (int i = 0; i < 1001; i++)
        {
            if (dp1[i] != 0 && dp2[i] != 0)
            {
                for (int j = 0; j < min(dp1[i], dp2[i]); j++)
                    res.emplace_back(i);
            }
        }
        return res;
    }

    /**
     * 买卖股票的最佳时机
     */
    int maxProfit(vector<int> &prices)
    {
        int Min = prices[0], res = 0;
        for (int i = 1; i < prices.size(); i++)
        {
            if ((prices[i] - Min) <= 0)
                Min = prices[i];
            else
                res = (prices[i] - Min) > res ? (prices[i] - Min) : res;
        }
        return res;
    }

    /**
     * 重塑矩阵
     */
    vector<vector<int>> matrixReshape(vector<vector<int>> &mat, int r, int c)
    {
        if (mat.size() * mat[0].size() != r * c)
            return mat;
        vector<vector<int>> res(r, vector<int>(c, 0));
        vector<int> dp;
        int k = 0;
        for (int i = 0; i < mat.size(); i++)
        {
            for (int j = 0; j < mat[0].size(); j++)
                dp.emplace_back(mat[i][j]);
        }
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
                res[i][j] = dp[k++];
        }
        return res;
    }

    /**
     * 杨辉三角
     */
    vector<vector<int>> generate(int numRows)
    {
        vector<vector<int>> res;
        for (int i = 0; i < numRows; i++)
        {
            vector<int> tem(i + 1, 1);
            for (int j = 1; (j > 0) && (j < i); j++)
                tem[j] = res[i - 1][j - 1] + res[i - 1][j];
            res.emplace_back(tem);
        }
        return res;
    }

    /**
     * 有效的数独
     */
    bool isValidSudoku(vector<vector<char>> &board)
    {
        unordered_set<char> dp;
        int a = 0, b = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    if (dp.insert(board[i][j]).second == false)
                        return false;
                }
            }
            dp.clear();
        }

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[j][i] != '.')
                {
                    if (dp.insert(board[j][i]).second == false)
                        return false;
                }
            }
            dp.clear();
        }

        for (int k = 0; k < 9; k++)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    if (board[a + i][b + j] != '.')
                    {
                        if (dp.insert(board[a + i][b + j]).second == false)
                            return false;
                    }
                }
            }
            dp.clear();
            a += 3;
            if (a == 9)
            {
                a = 0;
                b += 3;
            }
        }
        return true;
    }

    /**
     * 矩阵置零
     */
    void setZeroes(vector<vector<int>> &matrix)
    {
        unordered_set<int> dp;
        for (int i = 0; i < matrix.size(); i++)
        {
            for (int j = 0; j < matrix[0].size(); j++)
            {
                if (matrix[i][j] == 0)
                {
                    dp.insert(i);
                    dp.insert(j + matrix.size());
                }
            }
        }
        for (auto row : dp)
        {
            if (row < matrix.size())
            {
                for (int i = 0; i < matrix[0].size(); i++)
                    matrix[row][i] = 0;
            }
        }
        for (auto col : dp)
        {
            if (col >= matrix.size())
            {
                for (int i = 0; i < matrix.size(); i++)
                    matrix[i][col - matrix.size()] = 0;
            }
        }
        return;
    }

    /**
     * 字符串中的第一个唯一字符
     */
    int firstUniqChar(string s)
    {
        vector<int> dp(26, 0);
        for (auto i : s)
            dp[i - 97]++;
        for (int i = 0; i < s.size(); i++)
        {
            if (dp[s[i] - 97] == 1)
                return i;
        }
        return -1;
    }

    /**
     * 赎金信
     */
    bool canConstruct(string ransomNote, string magazine)
    {
        vector<int> a(26, 0);

        for (auto i : ransomNote)
            a[i - 'a']++;
        for (auto i : magazine)
        {
            a[i - 'a']--;
            if (a[i - 'a'] < 0)
                return false;
        }
        return true;
    }

    /**
     * 有效的字母异位词
     */
    bool isAnagram(string s, string t)
    {
        vector<int> a(26, 0);

        for (auto c : s)
            a[c - 'a']++;
        for (auto c : t)
            a[c - 'a']--;
        for (int i = 0; i < 26; i++)
            if (a[i] != 0)
                return false;

        return true;
    }

    /**
     * 环形链表
     */
    bool hasCycle(ListNode *head)
    {
        unordered_set<ListNode *> dp;
        while (head != nullptr)
        {
            if (dp.insert(head).second == false)
                return true;
            head = head->next;
        }
        return false;
    }

    /**
     * 合并两个有序链表
     */
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
    {
        ListNode *res = new ListNode(-1);
        ListNode *head = res;

        while (list1 != nullptr && list2 != nullptr)
        {
            if (list1->val < list2->val)
            {
                head->next = list1;
                list1 = list1->next;
            }
            else
            {
                head->next = list2;
                list2 = list2->next;
            }
            head = head->next;
        }

        if (list1 != nullptr)
            head->next = list1;
        else if (list2 != nullptr)
            head->next = list2;

        return res->next;
    }

    /**
     * 移除链表元素
     */
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode *res = head;
        ListNode *pre = head;
        if (head == nullptr)
            return nullptr;

        // if(head->next == nullptr){
        //     if(head->val == val)
        //         return nullptr;
        //     else
        //         return head;
        // }
        // head = head->next;

        while (head == pre && head->val == val)
        {
            head = head->next;
            pre = pre->next;
        }
        res = pre;
        head = head->next;

        while (head != nullptr)
        {
            if (head->val == val)
            {
                pre->next = head->next;
                head = pre->next;
            }
            else
            {
                head = head->next;
                pre = pre->next;
            }
        }
        return res;
    }

    /**
     * 反转链表
     */
    ListNode *reverseList(ListNode *head)
    {
        stack<ListNode *> dp;
        while (head->next != nullptr)
        {
            dp.emplace(head);
            head = head->next;
        }

        ListNode *res = head;
        while (dp.size() != 0)
        {
            head->next = dp.top();
            dp.pop();
            head = head->next;
        }
        return res;
    }

    /**
     * 删除排序链表中的重复元素
     */
    ListNode *deleteDuplicates(ListNode *head)
    {
        ListNode *res = new ListNode(-101);
        ListNode *pre = res;
        res->next = head;
        int tem = res->val;
        while (head != nullptr)
        {
            if (tem == head->val)
            {
                pre->next = head->next;
                head = pre->next;
            }
            else
            {
                tem = head->val;
                head = head->next;
                pre = pre->next;
            }
        }
        return res->next;
    }

    /**
     * 有效的括号
     */
    bool isValid(string s)
    {
        unordered_map<char, char> data;
        data[')'] = '(';
        data['}'] = '{';
        data[']'] = '[';

        stack<char> dp;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')
                dp.emplace(s[i]);
            if (s[i] == ')' || s[i] == '}' || s[i] == ']')
            {
                if (dp.size() == 0 || dp.top() != data[s[i]])
                    return false;
                else
                    dp.pop();
            }
        }
        if (dp.size() != 0)
            return false;
        return true;
    }

    /**
     * 二叉树的前序遍历（递归）
     */
    vector<int> res;
    vector<int> preorderTraversal(TreeNode *root)
    {
        if (root == nullptr)
            return res;
        res.emplace_back(root->val);
        preorderTraversal(root->left);
        preorderTraversal(root->right);

        return res;
    }

    /**
     * 二叉树的后序遍历（迭代）
     */
    vector<int> postorderTraversal(TreeNode *root)
    {
        vector<int> res;
        stack<TreeNode *> dp;
        if (root)
            dp.emplace(root);

        while (!dp.empty())
        {
            TreeNode *tem = dp.top();
            dp.pop();
            res.emplace_back(tem->val);

            if (tem->left)
                dp.emplace(tem->left);

            if (tem->right)
                dp.emplace(tem->right);
        }
        reverse(res.begin(), res.end());
        return res;
    }

    /**
     * 二叉树的中序遍历（莫里斯）
     */
    vector<int> inorderTraversal(TreeNode *root)
    {
    }

    /**
     * 二叉树的层序遍历
     */
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        queue<TreeNode *> a, b;
        vector<vector<int>> res;
        vector<int> tem;

        if (root)
            a.emplace(root);
        while (!a.empty())
        {
            tem.emplace_back(a.front()->val);
            if (a.front()->left)
                b.emplace(a.front()->left);
            if (a.front()->right)
                b.emplace(a.front()->right);
            a.pop();

            if (a.empty())
            {
                swap(a, b);
                res.emplace_back(tem);
                tem.clear();
            }
        }
        return res;
    }

    /**
     * 二叉树的最大深度
     */
    int maxDepthD(TreeNode *root, int depth)
    {
        if (!root)
            return depth;
        int left = maxDepthD(root->left, depth + 1);

        int right = maxDepthD(root->right, depth + 1);

        return max(left, right);
    }
    int maxDepth(TreeNode *root)
    {
        return maxDepthD(root, 0);
    }

    /**
     *  对称二叉树
     */
    bool Symmetric(TreeNode *left, TreeNode *right)
    {
        if (left == nullptr && right == nullptr)
            return true;
        if (left == nullptr || right == nullptr)
            return false;
        if (left->val != right->val)
            return false;
        return Symmetric(left->left, right->right) && Symmetric(left->right, right->left);
    }
    bool isSymmetric(TreeNode *root)
    {
        if (root == nullptr)
            return true;
        return Symmetric(root->left, root->right);
    }

    /**
     * 翻转二叉树
     */
    void Invert(TreeNode *root)
    {
        if (root == nullptr)
            return;
        TreeNode *tem = root->left;
        root->left = root->right;
        root->right = tem;
        Invert(root->left);
        Invert(root->right);
        return;
    }

    TreeNode *invertTree(TreeNode *root)
    {
        Invert(root);
        return root;
    }

    /**
     * 路径总和
     */
    bool Path(TreeNode *root, int targetSum, int total)
    {
        bool left, right;
        if (root->left == nullptr && root->right == nullptr)
        {
            if (total == targetSum)
                return true;
        }
        if (root->left)
            left = Path(root->left, targetSum, total + root->left->val);
        if (root->right)
            right = Path(root->right, targetSum, total + root->right->val);
        return left || right;
    }
    bool hasPathSum(TreeNode *root, int targetSum)
    {
        if (root == nullptr)
            return false;
        return Path(root, targetSum, root->val);
    }

    
};

int main()
{
    Solution s;
    // vector<vector<int>> q;
    // vector<int> a = {0, 1, 2, 0};
    // vector<int> b = {3, 4, 5, 2};
    // vector<int> c = {1, 3, 1, 5};
    // q.emplace_back(a);
    // q.emplace_back(b);
    // q.emplace_back(c);
    // s.setZeroes(q);
    // printf("%d",'c');

    // s.hasCycle();
    return 0;
}