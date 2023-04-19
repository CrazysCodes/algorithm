package Code;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Deque;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Map.Entry;

public class exam {
    public static void main(String[] args) {
        // System.out.println((new Random().nextInt() % 100) < 60 ? "YES" : "NO");
        test t = new test();
        t.t1();
    }
}

class test {
    /*
     * 10 5 6
     * 1 2 3 4 5 6 7 8 9 10
     */
    void t1() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt(); // 个数
        int price = in.nextInt(); // 价位
        in.nextLine();
        int[] dp = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(dp);
        int index = 0, min = Integer.MAX_VALUE;
        for (int i = 0; i < dp.length; i++) {
            if (Math.abs(dp[i] - price) < min) {
                index = i;
                min = Math.abs(dp[i] - price);
            }
        }
        int left = index, right = index;
        List<Integer> res = new ArrayList<>();
        res.add(dp[index]);
        while (m == 0) {
            if (left == 0) {
                res.add(dp[++right]);
            } else if (right == n - 1) {
                res.add(dp[--left]);
            } else if (Math.abs(dp[left - 1] - price) <= Math.abs(dp[right + 1] - price)) {
                res.add(dp[--left]);
            } else {
                res.add(dp[++right]);
            }
            m--;
        }
        Collections.sort(res);
        String s = "";
        for (Integer integer : res) {
            s += integer + " ";
        }
        System.out.println(s.substring(0, s.length()));
    }

    /*
     * 11 员工个数 0~n-1
     * 4 4 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 2 2 30天数量
     * 0 1 7 10 每一天员工id
     */
    void t2() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();// 员工个数
        int[] flag = new int[n];
        in.nextLine();
        in.nextLine();
        Map<Integer, Integer> dp = new HashMap<>();
        for (int i = 0; i < 30; i++) {
            int[] data = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
            for (int j : data) {
                if (flag[j] == 0)
                    flag[j] = i + 1;
                dp.put(j, dp.getOrDefault(j, 0) + 1);
            }
        }
        List<Map.Entry<Integer, Integer>> list = new ArrayList<>(dp.entrySet());
        list.sort((a, b) -> {
            if (a.getValue() < b.getValue())
                return 1;
            else if (a.getValue() == b.getValue()) {
                if (flag[a.getKey()] > flag[b.getKey()])
                    return 1;
                else if (flag[a.getKey()] == flag[b.getKey()]) {
                    if (a.getKey() > b.getKey()) {
                        return 1;
                    }
                }
            }
            return -1;
        });
        String res = "";

        for (int i = 0; i < Math.min(5, list.size()); i++) {
            res += list.get(i).getKey() + " ";
        }
        System.out.println(res.substring(0, res.length()));
    }

    /*
     * Life is painting a picture, not doing 'a sum'.
     * 8 15,20 26,43 45
     * Life is painting a picture, not doing 'a sum'.
     * [8, 15][19, 25][42, 44]
     */
    String space(String str, List<int[]> dp, List<int[]> data) {
        boolean flag = false;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == ' ') {
                if (flag) {
                    str = str.substring(0, i) + str.substring(i + 1, str.length()); // 确定需要去除空格
                    for (int j = data.size() - 1; j >= 0; j--) {
                        if (data.get(j)[0] > i) {
                            data.get(j)[0]--;
                            data.get(j)[1]--;
                        } else {
                            break;
                        }
                    }
                } else {
                    flag = true;
                    for (int[] js : dp) {
                        if (i > js[0] && i < js[1]) {
                            flag = false;
                            break;
                        }
                    }
                }
            } else {
                flag = false;
            }
        }
        return str;
    }

    void t3() {
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            String str = in.nextLine(); // 字符串
            List<int[]> data = new ArrayList<>(); // 初始关键词索引

            String[] s = in.nextLine().split(",");
            for (String string : s) {
                int[] temi = Arrays.stream(string.split(" ")).mapToInt(Integer::parseInt).toArray();
                data.add(temi);
            }
            int countt = 0;
            List<int[]> tem = new ArrayList<>(); // 字符 ‘的索引
            for (int i = 0; i < str.length(); i++) {
                if (str.substring(i, i + 1).equals("'")) {
                    countt++;
                    if (countt % 2 != 0) {
                        int[] tt = new int[2];
                        tt[0] = i;
                        tem.add(tt);
                    } else {
                        tem.get(tem.size() - 1)[1] = i;
                    }
                }
            }
            str = space(str, tem, data);
            String res = "";
            for (int[] is : data) {
                List<Integer> cnt = new ArrayList<>();
                cnt.add(is[0]);
                cnt.add(is[1]);
                res += cnt.toString();
                cnt.clear();
            }
            System.out.println(str);
            System.out.println(res);
        }
    }

    void t4() {
        Scanner in = new Scanner(System.in);
        while (in.hasNext()) {
            String str = in.nextLine(); // 字符串
            List<int[]> data = new ArrayList<>(); // 初始关键词索引
            List<String> nums = new ArrayList<>(); // 关键词列表

            String[] s = in.nextLine().split(",");
            for (String string : s) {
                int[] temi = Arrays.stream(string.split(" ")).mapToInt(Integer::parseInt).toArray();
                data.add(temi);
                nums.add(str.substring(temi[0], temi[1] + 1));
            }
            int countt = 0;
            List<int[]> tem = new ArrayList<>(); // 字符 ‘的索引
            for (int i = 0; i < str.length(); i++) {
                if (str.substring(i, i + 1).equals("'")) {
                    countt++;
                    if (countt % 2 != 0) {
                        int[] tt = new int[2];
                        tt[0] = i;
                        tem.add(tt);
                    } else {
                        tem.get(tem.size() - 1)[1] = i;
                    }
                }
            }
            str = space(str, tem);
            String res = "";
            for (String string : nums) {
                List<Integer> cnt = new ArrayList<>();
                cnt.add(str.indexOf(string));
                cnt.add(str.indexOf(string) + string.length() - 1);
                res += cnt.toString();
                cnt.clear();
            }
            System.out.println(str);
            System.out.println(res);
        }
    }

    private static String space(String str, List<int[]> dp) {
        boolean flag = false;
        for (int i = 0; i < str.length(); i++) {
            if (str.charAt(i) == ' ') {
                if (flag)
                    str = str.substring(0, i) + str.substring(i + 1, str.length());
                else {
                    flag = true;
                    for (int[] js : dp) {
                        if (i > js[0] && i < js[1]) {
                            flag = false;
                            break;
                        }
                    }
                }
            } else {
                flag = false;
            }
        }
        return str;
    }
}