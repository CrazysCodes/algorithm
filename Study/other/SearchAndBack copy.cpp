#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
public:
    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

    vector<int> twoSum(vector<int> &nums, int target)
    {
        unordered_map<int, int> index;
        for (int i = 0; i < nums.size(); i++)
        {
            unordered_map<int, int>::iterator iter = index.find(target - nums[i]);
            if (iter != index.end())
            {
                return {iter->second, i};
            }
            index[nums[i]] = i;
        }
        return {};
    }

    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        stack<int> L1;
        stack<int> L2;
        while (l1 != NULL)
        {
            L1.emplace(l1->val);
            l1 = l1->next;
        }
        while (l2 != NULL)
        {
            L2.emplace(l2->val);
            l2 = l2->next;
        }
        int n1 = L1.size(), n2 = L2.size();
        int sum = 0;
        for (int i = 0; i < n1; i++)
        {
            sum += L1.top() * pow(10, --n1);
            L1.pop();
        }
        for (int i = 0; i < n2; i++)
        {
            sum += L2.top() * pow(10, --n2);
            L1.pop();
        }
        ListNode *head = new ListNode(sum % 10);
        ListNode *tail = head;
        sum /= 10;
        while (sum > 0)
        {
            ListNode *tem = new ListNode(sum % 10);
            tail->next = tem;
            tail = tem;
            sum /= 10;
        }
        return head;
    }
    int lengthOfLongestSubstring(string s)
    {
    }

private:
};
int main()
{
    Solution s;
    

    return 0;
}
