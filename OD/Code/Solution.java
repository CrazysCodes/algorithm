package Code;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * 力扣华为机试
 */

public class Solution {
    public static void main(String[] args) {
        // List<String> tem = new
        // ArrayList<>(Arrays.asList("mobile","mouse","moneypot","monitor","mousepad"));
        String[] da = { "mobile", "mouse", "moneypot", "monitor", "mousepad" };
        Solution s = new Solution();
        // List<List<String>> res = new ArrayList<List<String>>();
        // res = s.suggestedProducts(da, "mouse");
        s.longestPalindrome("babad");
    }

    /**
     * 最长回文子串 动态规划()
     * 
     * @param s
     * @return
     */
    public String longestPalindrome(String s) {

        String res = String.valueOf(s.charAt(0));
        int len = s.length();
        boolean[][] dp = new boolean[len][len];
        for (int i = 0; i < dp.length; i++)
            dp[i][i] = true;

        for (int i = 2; i <= len; i++) {
            for (int j = 0; j < len - i + 1; j++) {
                int t = i + j - 1;
                if (s.charAt(j) != s.charAt(t))
                    dp[j][t] = false;
                else {
                    if (i < 3)
                        dp[j][t] = true;
                    else
                        dp[j][t] = dp[j + 1][t - 1];
                }
                if (dp[j][t] && i > res.length())
                    res = s.substring(j, t + 1);
            }
        }
        return res;
    }

    /**
     * 搜索推荐系统 双指针
     * 
     * @param products
     * @param searchWord
     * @return
     */
    public List<List<String>> suggestedProducts(String[] products, String searchWord) {
        List<List<String>> res = new ArrayList<List<String>>();
        int left = 0, right = products.length;
        Arrays.sort(products);

        for (int i = 0; i < searchWord.length(); i++) {
            while (left < right && !products[left].matches(searchWord.substring(0, i + 1) + ".*"))
                left++;
            while (left < right && !products[right - 1].matches(searchWord.substring(0, i + 1) + ".*"))
                right--;

            List<String> tem = new ArrayList<String>();
            for (int j = left; j < right && j < left + 3; j++)
                tem.add(products[j]);
            res.add(new ArrayList<>(tem));
        }
        return res;
    }

    /**
     * 盛最多水的容器
     * 
     * @param height
     * @return
     */
    public int maxArea(int[] height) {
        int res = 0;
        int left = 0, right = height.length - 1;

        while (left != right) {
            res = Math.max(res, (right - left) * Math.min(height[left], height[right]));
            if (height[left] > height[right]) {
                right--;
            } else {
                left++;
            }
        }

        return res;
    }
}
