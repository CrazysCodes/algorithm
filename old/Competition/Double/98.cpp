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

    int minMaxDifference(int num)
    {
        auto data = to_string(num);
        string mind = data;
        char d = data[0];
        int i = 0;
        while (data[i] == '9')
            i++;
        d = data[i];

        replace(data.begin(), data.end(), d, '9');
        int max = atoi(data.c_str());

        i = 0;
        while (mind[i] == '0')
            i++;
        d = mind[i];
        replace(mind.begin(), mind.end(), d, '0');
        int min = 0;

        int len = mind.size() - 1;
        for (auto i : mind)
        {
            min += (i - 48) * pow(10, len);
            len--;
        }

        return max - min;
    }

    int minimizeSum(vector<int> &nums)
    {
    }
};

int main()
{
    Solution s;
    vector<int> a = {1, 2, 2, 1};
    vector<int> b = {2, 2};
    vector<int> c = {2};
    // cout << s.minMaxDifference(90);
    int i = 1 | 2;
    cout << i;

    return 0;
}