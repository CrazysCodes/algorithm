#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class solution
{

    struct ListNode
    {
        int val;
        ListNode *next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode *next) : val(x), next(next) {}
    };

public:
    ListNode *getKthFromEnd(ListNode *head, int k)
    {
        ListNode *tem = head;
        int len = 0;
        while (tem != NULL)
        {
            len++;
            tem = tem->next;
        }
        for (int i = 0; i < len - k; i++)
        {
            head = head->next;
        }
        return head;
    }

    void rotate(vector<int> &nums, int k)
    {
        vector<int> dp(k, 0);
        int n = nums.size();
        for (int i = n - 1, j = k - 1; i >= 0; i--)
        {
            if (j >= 0)
                dp[j--] = nums[i];
            else
                nums[i + k] = nums[i];
        }
        for (int i = 0; i < k; i++)
        {
            nums[i] = dp[i];
        }
    }

    int findClosestNumber(vector<int> &nums)
    {
        int min = 100000, res = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            if (abs(nums[i]) < abs(min))
                min = nums[i];
            else if (abs(nums[i]) == abs(min) && (nums[i] > min))
                min = nums[i];
        }
        return min;
    }

    void reorderList(ListNode *head)
    {
        ListNode *tem = head;
        deque<ListNode *> data;
        bool flag = true;
        while (tem != NULL)
        {
            data.push_back(tem);
            tem = tem->next;
        }
        head = data.front();
        while (!data.empty())
        {
            if (flag)
            {
                if (data.size() == 1)
                {
                    data.front()->next = NULL;
                    data.pop_front();
                }
                else
                {
                    data.front()->next = data.back();
                    data.pop_front();
                    flag = false;
                }
            }
            else
            {
                if (data.size() == 1)
                {
                    data.front()->next = NULL;
                    data.pop_front();
                }
                else
                {
                    data.back()->next = data.front();
                    data.pop_back();
                    flag = true;
                }
            }
        }
    }
};

int main()
{
    solution s;

    return 0;
}