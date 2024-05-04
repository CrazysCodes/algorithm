#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool exist(vector<vector<char>> &board, string word)
    {
        rows = board.size();
        cols = board[0].size();
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (dfs(board, word, i, j, 0))
                    return true;
            }
        }
        return false;
    }

private:
    int rows, cols;
    bool dfs(vector<vector<char>> &board, string word, int x, int y, int index)
    {
        if (x >= rows || x < 0 || y >= cols || y < 0 || board[x][y] != word[index])
            return false;
        if (index == word.size() - 1)
            return true;
        board[x][y] = '\0';
        bool res = dfs(board, word, x + 1, y, index + 1) || dfs(board, word, x - 1, y, index + 1) ||
                   dfs(board, word, x, y + 1, index + 1) || dfs(board, word, x, y - 1, index + 1);
        board[x][y] = word[index];
        return res;
    }
};
int main()
{
    Solution s;
    vector<vector<char>> dp = vector<vector<char>>(3, vector<char>(4)) = {{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
    // vector<int> dp = {};
    cout << (1 << 3);
    return 0;
}
