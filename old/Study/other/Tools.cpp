#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    void toupper()
    {
        string str = "10";
        while (str[0] != '-')
        {
            cout << "请输入字符串(全转大写):" << endl;
            cin >> str;
            transform(str.begin(), str.end(), str.begin(), ::toupper);
            cout << str << endl;
        }
        return;
    }

private:
};
typedef struct error_info
{
    void *handle; // void *
    int __error_number;
    char *__error_message; // char *
    char *sqlstate;        // char *
} error_info;
int main()
{
    Solution s;
    s.toupper();

    return 0;
}
