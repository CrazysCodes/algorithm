package Code;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Map.Entry;

/**
 * 2023 OD真题
 */

class Problem {

    /*
     * 选择两道100分题目、一道50分题目 多次调用不重复(已选的写入文件)
     */
    void num() {
        BufferedReader reader;
        OutputStream out = null; // 内存输出流
        BufferedWriter bw = null;
        int[] a = new int[50];
        int[] b = new int[49];
        int r;
        try {
            reader = new BufferedReader(new FileReader(
                    "num.txt"));
            String da = reader.readLine();
            String db = reader.readLine();
            reader.close();

            String[] na = da.split(" ");
            String[] nb = db.split(" ");
            for (String s1 : na) {
                a[Integer.parseInt(s1)] = 1;
            }
            for (String s1 : nb) {
                b[Integer.parseInt(s1)] = 1;
            }

            r = (int) (Math.random() * 50);
            for (int i = r; i < r + 50; i++) {
                if (a[i % 50] != 1) {
                    a[i % 50] = 1;
                    da += " " + String.valueOf(r);
                    break;
                }
            }
            r = (int) (Math.random() * 50);
            for (int i = r; i < r + 50; i++) {
                if (a[i % 50] != 1) {
                    a[i % 50] = 1;
                    da += " " + String.valueOf(r);
                    break;
                }
            }
            r = (int) (Math.random() * 49);
            for (int i = r; i < r + 49; i++) {
                if (b[i % 49] != 1) {
                    b[i % 49] = 1;
                    db += " " + String.valueOf(r);
                    break;
                }
            }

            out = new FileOutputStream("num.txt");
            bw = new BufferedWriter(new OutputStreamWriter(out, "utf-8"));
            bw.write(da); // 数据写入缓冲区，一般在内存中
            bw.newLine(); // 写入换行符
            bw.write(db); // 数据写入缓冲区，一般在内存中
            bw.flush();

            System.out.println(da);
            System.out.println(db);
        } catch (Exception e) {
            System.out.println("Exception");
        }
    }

    /**
     * 猜字谜 两重for循环暴力
     */
    void t1() {
        Scanner in = new Scanner(System.in);

        String a = in.nextLine();
        String b = in.nextLine();
        String[] da = a.split(",");
        String[] db = b.split(",");
        boolean flag = true;

        List<String> res = new ArrayList<>();

        for (String s1 : da) {
            for (String s2 : db) {
                if (test1(s1, s2) || test2(s1, s2)) {
                    res.add(s2);
                    flag = false;
                    break;
                }
            }
            if (flag)
                res.add("not found");

            flag = true;
        }
        System.out.println(res.toString());
    }

    // 判断排序后两者是否相同
    boolean test1(String a, String b) {
        char[] s1 = a.toCharArray();
        char[] s2 = b.toCharArray();
        Arrays.sort(s1);
        Arrays.sort(s2);
        return Arrays.equals(s1, s2);
    }

    // 判断去重后两者是否相同
    boolean test2(String a, String b) {
        HashSet<Character> d = new HashSet<>();
        HashSet<Character> e = new HashSet<>();
        for (int i = 0; i < a.length(); i++)
            d.add(a.charAt(i));
        for (int i = 0; i < b.length(); i++)
            e.add(b.charAt(i));
        return d.equals(e);
    }

    /**
     * 木板题
     */
    void t2() {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt();
        int count = in.nextInt();
        in.nextLine();

        int[] arr = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(arr);
        while (count > 0) {
            for (int i = 1; i < arr.length; i++) {
                if (arr[i - 1] != arr[i]) {
                    arr[i - 1]++;
                    break;
                }
                if (i == arr.length - 1)
                    arr[arr.length - 1]++;
            }
            count--;
        }
        System.out.println(arr[0]);
    }

    /*
     * 最长公共子串 (双指针)（暴力）
     */
    void t3() {
        // Scanner in = new Scanner(System.in);
        // String a = in.nextLine();
        // String b = in.nextLine();
        // String max_s = "", tem;
        // int max = 0;
        // if (a.length() < b.length()) {
        // tem = a;
        // a = b;
        // b = tem;
        // }
        // for (int i = 0; i < b.length(); i++) {
        // for (int j = i + 1; j <= b.length(); j++) {
        // tem = b.substring(i, j);
        // if (tem.length() > max) {
        // if (a.contains(tem)) {
        // max = tem.length();
        // max_s = tem;
        // }
        // }
        // }
        // }
        // System.out.println(max_s);
        Scanner in = new Scanner(System.in);
        String a = in.nextLine();
        String b = in.nextLine();

        String max_s = "", tem;
        int max = 0, left = 0, right = 1;
        while (right <= a.length()) {
            tem = a.substring(left, right);
            if (b.contains(tem)) {
                if (tem.length() > max) {
                    max_s = tem;
                    max = tem.length();
                }
            } else
                left++;
            right++;
        }

        System.out.println(max_s);
    }

    /*
     * 查找单入口空闲区域 (暴力搜索)
     */
    void t4() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        int max = -1, max_i = 0, max_j = 0;
        boolean flag = false;
        in.nextLine();
        String[][] data = new String[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                data[i][j] = in.next();
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i != 0 && i != n - 1 && j != 0 && j != m - 1) {
                    continue;
        }
                if (data[i][j].equals("O")) {
                    int tem = bfs(data, i, j, 0);
                    if (tem > 0) {
                        if (tem > max) {
                            max = tem;
                            max_i = i;
                            max_j = j;
                            flag = false;
                        } else if (tem == max) {
                            flag = true;
                        }
                    }
                }
            }
        }
        if (max != -1) {
            if (flag)
                System.out.println(max);
            else
                System.out.println(max_i + " " + max_j + " " + max);
        } else {
            System.out.println("NULL");
        }
    }

    int bfs(String[][] data, int i, int j, int count) {
        boolean flag = false;
        if (count != 0) {
            if (i < 0 || i == data.length || j < 0 || j == data[0].length) {
                return count;
            } else {
                if (data[i][j].equals("X")) {
                    return count;
                } else {
                    data[i][j] = "X";
                    flag = true;
                    if (i == 0 || i == data.length - 1 || j == 0 || j == data[0].length - 1) {
                        return -1;
                    }
                }
            }
        }
        if (data[i][j].equals("O") || flag) {
            data[i][j] = "X";
            int a = bfs(data, i - 1, j, count + 1);
            int b = bfs(data, i, j - 1, count + 1);
            int c = bfs(data, i + 1, j, count + 1);
            int d = bfs(data, i, j + 1, count + 1);
            if (a < 0 || b < 0 || c < 0 || d < 0) {
                count = Integer.MIN_VALUE;
            } else {
                int[] t = { a, b, c, d };
                Arrays.sort(t);
                count = t[3];
            }
        }
        return count;
    }

    /*
     * 单词倒序（逆向输出）
     */
    void t5() {
        Scanner in = new Scanner(System.in);
        String a = in.nextLine();
        String res = "";
        for (int i = a.length() - 1; i >= 0; i--) {
            char tem = a.charAt(i);
            if (tem == '.' || tem == ' ' || tem == '?' || tem == ',') {
                res = tem + res;
            } else {
                String b = "";
                while (tem != '.' && tem != ' ' && tem != '?' && tem != ',') {
                    b += tem;
                    i--;
                    if (i < 0)
                        break;

                    tem = a.charAt(i);
                }
                i++;
                res = b + res;
            }
        }
        System.out.println(res);
    }

    /*
     * 打印文件 (哈希表)
     */
    void t6() {
        Scanner in = new Scanner(System.in);
        Map<String, List<task>> data = new HashMap<>();
        List<String> res = new ArrayList<>();
        int n = in.nextInt();
        in.nextLine();

        for (int i = 0; i < n; i++) {
            String tem = in.nextLine();
            String[] d = tem.split(" ");
            if (d[0].equals("IN")) {
                task t = new task(i + 1, Integer.parseInt(d[2]));
                if (!data.containsKey(d[1])) {
                    List<task> dp = new ArrayList<>();
                    dp.add(t);
                    data.put(d[1], dp);
                } else {
                    data.get(d[1]).add(t);
                }
            } else {
                if (!data.containsKey(d[1])) {
                    res.add("NULL");
                } else {
                    List<task> dp = data.get(d[1]);
                    if (dp.size() == 0) {
                        res.add("NULL");
                        continue;
                    }
                    dp.sort((a, b) -> {
                        return b.type - a.type;
                    });
                    res.add(String.valueOf(dp.get(0).id));
                    dp.remove(0);
                }
            }
        }
        for (String string : res) {
            System.out.println(string);
        }
    }

    /*
     * 对称字符串 (二分法)
     */
    void t7() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();

        List<String> res = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            int a = in.nextInt();
            long b = in.nextLong();
            int count = 0;
            while (a > 1) {
                if (b < Math.pow(2, a - 1) / 2) {
                    count++;
                } else {
                    b -= Math.pow(2, a - 1) / 2;
                }
                a--;
            }
            if (count % 2 == 0)
                res.add("red");
            else
                res.add("blue");
        }
        for (String string : res) {
            System.out.println(string);
        }
    }

    /*
     * 分界线 (暴力)
     */
    void t8() {
        Scanner in = new Scanner(System.in);
        String[] arra = in.nextLine().split(" ");
        String[] arrb = in.nextLine().split(" ");
        for (int i = 0; i < arrb.length; i++) {
            char[] tema = arrb[i].toCharArray();
            Arrays.sort(tema);

            boolean flag = false;
            for (int j = 0; j < arra.length; j++) {
                char[] temb = arra[j].toCharArray();
                Arrays.sort(temb);
                if (Arrays.equals(tema, temb)) {
                    flag = true;
                    break;
                }
            }
            if (!flag) {
                System.out.println(false);
                return;
            }
        }
        System.out.println(true);
    }

    /*
     * 关联端口组合并
     */
    void t9() {
        Scanner in = new Scanner(System.in);
        int m = Integer.parseInt(in.nextLine());
        Set<String> set = new TreeSet<>();
        List<Set<String>> data = new ArrayList<>();
        if (m < 1 || m > 10) {
            System.out.println("[[]]");
            return;
        }

        // 对所有端口组 去重、组内排序 并且合并
        for (int i = 0; i < m; i++) {
            String[] t = in.nextLine().split(",");
            for (String s : t) {
                set.add(s);
            }
            data.add(new HashSet<>(set));
            if (set.size() > 1)
                merge(data, set, i);
            set.clear();
        }
        System.out.println(data.toString());
    }

    // 合并端口组
    void merge(List<Set<String>> data, Set<String> target, int index) {
        for (int i = 0; i < data.size(); i++) {
            if (i == index)
                continue;
            Set<String> tem = new HashSet<>(data.get(i));
            tem.retainAll(target); // 求并集
            if (tem.size() > 1) { // 可合并
                target.addAll(data.get(i));
                data.get(i).clear();
                data.get(i).addAll(target);
                data.remove(index);
                merge(data, data.get(i), i);
                return;
            }
        }
    }

    /*
     * 货币单位换算
     */
    private static Map<String, Double> map = new HashMap<String, Double>() {
        {
            put("CNY", 1.0);
            put("fen", 100.0);
            put("JPY", 18.25);
            put("sen", 1825.0);
            put("HKD", 1.230);
            put("cents", 123.0);
            put("EUR", 0.14);
            put("eurocents", 14.0);
            put("GBP", 0.12);
            put("pence", 12.0);
        }
    };

    void t10() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        double res = 0.0;
        for (int i = 0; i < n; i++) {
            String tems = in.nextLine();
            String[] data = tems.split("\\d");
            double temd = 0.0;
            int index = 0;
            for (int j = 0; j < data.length; j++) {
                if (!data[j].equals("")) {
                    temd += Integer.parseInt(tems.substring(index, tems.indexOf(data[j]))) * 100 / map.get(data[j]);
                    index = j + data[j].length();
                }
            }
            res += temd;
        }
        System.out.println((int) res);
    }

    /*
     * 完美走位 (哈希表)
     */
    void t11() {
        Scanner in = new Scanner(System.in);
        String a = in.nextLine();

        int avg = a.length() / 4;
        Map<Character, Integer> dp = new HashMap<>();
        for (int i = 0; i < a.length(); i++)
            dp.put(a.charAt(i), dp.getOrDefault(a.charAt(i), 0 - avg) + 1);

        int min = a.length();
        for (int i = 0; i < a.length(); i++) {
            HashMap<Character, Integer> cp = new HashMap<>(dp);
            int len = 0;
            boolean flag = false;
            if (cp.get(a.charAt(i)) > 0) {
                for (int j = i; j < a.length(); j++) {
                    cp.put(a.charAt(j), cp.get(a.charAt(j)) - 1);
                    len++;
                    if (isPerfect(cp)) {
                        flag = true;
                        break;
                    }
                }
            }
            if (flag)
                min = Math.min(min, len);
        }
        System.out.println(min);
    }

    boolean isPerfect(HashMap<Character, Integer> cp) {
        for (Character value : cp.keySet()) {
            if (cp.get(value) > 0)
                return false;
        }
        return true;
    }

    /*
     * 简单的自动曝光 (数学问题)
     */
    void t12() {
        Scanner in = new Scanner(System.in);
        int[] num = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int sum = Arrays.stream(num).sum();
        double avg = sum / num.length;
        int res = (int) (128 - avg);

        for (int i = res + 1; i <= 128; i++) {
            double count = 0;
            for (int j = 0; j < num.length; j++) {
                if (num[j] + i > 255) {
                    count += 255;
                } else if (num[j] + i < 0) {
                    count += 0;
                } else {
                    count += num[j] + i;
                }
            }
            if (Math.abs(count / num.length - 128) < Math.abs(avg - 128)) {
                res = i;
                avg = count / num.length;
            } else {
                break;
            }
        }
        for (int i = res; i >= -128; i--) {
            double count = 0;
            for (int j = 0; j < num.length; j++) {
                if (num[j] + i > 255) {
                    count += 255;
                } else if (num[j] + i < 0) {
                    count += 0;
                } else {
                    count += num[j] + i;
                }
            }
            if (Math.abs(count / num.length - 128) <= Math.abs(avg - 128)) {
                res = i;
                avg = count / num.length;
            } else {
                break;
            }
        }
        System.out.println(res);
    }

    /*
     * 日志采集系统
     */
    void t13() {
        Scanner in = new Scanner(System.in);
        int[] nums = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int res = 0;
        for (int i = 0; i < nums.length; i++) {
            int sum = 0, count = 0;
            for (int j = 0; j <= i; j++) {
                sum += nums[j];
                if (sum >= 100) {
                    count += (100 - sum + nums[j]) * (j - i + 1);
                    break;
                } else
                    count += nums[j] * (j - i + 1);
            }
            res = Math.max(count, res);
            if (sum >= 100) {
                break;
            }
        }
        System.out.println(res);
    }

    /*
     * 数组的中心位置
     */
    void t14() {
        Scanner in = new Scanner(System.in);
        int[] nums = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int mul = 1, left = 1;
        for (int i : nums)
            mul *= i;
        for (int i = 0; i < nums.length; i++) {
            if (left == mul / nums[i]) {
                System.out.println(i);
                return;
            } else {
                left *= nums[i];
                mul /= nums[i];
            }
        }
        System.out.println(-1);
    }

    /*
     * 通信误码
     */
    void t15() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        List<Integer> nums = new ArrayList<>();
        Map<Integer, Integer> dp = new HashMap<>();
        for (int i = 0; i < n; i++) {
            int tem = in.nextInt();
            nums.add(tem);
            dp.put(tem, dp.getOrDefault(tem, 0) + 1);
        }
        int max = 0;
        List<Integer> res = new ArrayList<>();
        for (Integer i : dp.keySet()) {
            if (dp.get(i) > max) {
                res.clear();
                res.add(i);
                max = dp.get(i);
            } else if (dp.get(i) == max) {
                res.add(i);
            }
        }
        int min = nums.size();
        for (Integer i : res) {
            min = Math.min(nums.lastIndexOf(i) - nums.indexOf(i) + 1, min);
        }
        System.out.println(min);
    }

    /*
     * 网上商城优惠活动（一）
     */
    void t16() {

    }

    /*
     * 开心消消乐 深搜广搜
     */
    void t17() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        in.nextLine();
        int[][] nums = new int[n][m];
        int res = 0;
        for (int i = 0; i < n; i++) {
            String[] tems = in.nextLine().split(" ");
            for (int j = 0; j < m; j++) {
                nums[i][j] = Integer.parseInt(tems[j]);
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (nums[i][j] == 1) {
                    search(nums, n, m, i, j);
                    res++;
                }
            }
        }
        System.out.println(res);
    }

    void search(int[][] nums, int n, int m, int x, int y) {
        nums[x][y] = 0;
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i >= 0 && i < n && j >= 0 && j < m &&
                        nums[i][j] == 1) {
                    search(nums, n, m, i, j);
                }
            }
        }
    }

    /*
     * 获取最大软件版本号 字符串处理
     */
    void t18() {
        Scanner in = new Scanner(System.in);
        String a = in.nextLine();
        String b = in.nextLine();

        String[] tema = a.split("\\.");
        String[] temb = b.split("\\.");

        for (int i = 0; i < 2; i++) {
            int ta = Integer.valueOf(tema[i]);
            int tb = Integer.valueOf(temb[i]);
            if (ta != tb) {
                System.out.println(ta > tb ? a : b);
                return;
            }
        }

        if (tema.length > 2 && temb.length > 2) {
            String[] splitA2 = tema[2].split("-");
            String[] splitB2 = temb[2].split("-");
            int firstOneA = Integer.valueOf(splitA2[0]);
            int firstOneB = Integer.valueOf(splitB2[0]);
            // 比较增量版本
            if (firstOneA != firstOneB) {
                System.out.println(firstOneA > firstOneB ? a : b);
                return;
            }
            if (splitA2.length == 2 && splitB2.length == 2) {
                // 有里程碑版本
                System.out.println(splitA2[1].compareTo(splitB2[1]) >= 0 ? a : b);
            } else {
                System.out.println(splitA2.length >= splitB2.length ? a : b);
            }
        } else {
            System.out.println(tema.length >= temb.length ? a : b);
        }
    }

    /*
     * 寻找链表的中间结点 模拟链表
     */
    void t19() {
        Scanner in = new Scanner(System.in);
        int index = in.nextInt();
        int n = in.nextInt();
        Map<Integer, node> dp = new HashMap<>();
        for (int i = 0; i < n; i++) {
            int add = in.nextInt();
            int val = in.nextInt();
            int next = in.nextInt();
            dp.put(add, new node(val, next));
        }
        int[] nums = new int[n];
        for (int i = 0; i < n; i++) {
            nums[i] = dp.get(index).val;
            index = dp.get(index).next;
        }
        System.out.println(nums[n / 2]);
    }

    /*
     * 最小的调整次数
     */
    void t20() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        in.nextLine();
        int res = 0;
        int front = 0;
        boolean isResver = false;
        for (int i = 0; i < 2 * n; i++) {
            String[] str = in.nextLine().split(" ");
            if (str.length == 3) {
                if (front != 0) {
                    if (str[0].equals("head") && !isResver) {
                        isResver = true;
                    }
                }
                front++;
            } else if (str.length == 1) {
                front--;
                res += isResver ? 1 : 0;
                isResver = false;
            }
        }
        System.out.println(res);
    }

    /*
     * 通过车辆最多颜色 滑动窗口
     */
    void t30() {
        Scanner in = new Scanner(System.in);
        int[] dp = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int len = in.nextInt();
        int left = 0, right = left + len - 1, res = 0;
        Map<Integer, Integer> data = new HashMap<>();
        for (int i = 0; i < right; i++) {
            data.put(dp[i], data.getOrDefault(dp[i], 0) + 1);
        }
        while (right < dp.length) {
            data.put(dp[right], data.getOrDefault(dp[right], 0) + 1);
            if (left != 0)
                data.put(dp[left - 1], data.getOrDefault(dp[right], 0) - 1);
            List<Map.Entry<Integer, Integer>> list = new ArrayList<>(data.entrySet());
            list.sort((a, b) -> {
                if (a.getValue() < b.getValue()) {
                    return 1;
                }
                return -1;
            });
            res = Math.max(res, list.get(0).getValue());
            right++;
            left++;
        }
        System.out.println(res);
    }

    /*
     * 租车骑绿道
     */
    void t32() {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt(); // 限重
        int n = in.nextInt(); // 人数
        in.nextLine();
        int[] data = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(data);
        int left = 0, right = n - 1, res = 0;
        while (left <= right) {
            if (data[left] + data[right] <= m) {
                left++;
            }
            res++;
            right--;
        }
        System.out.println(res);
    }

    /*
     * 预定酒店 双指针
     * 错误想法:使用TreeMap排序 酒店价格可能重复
     */
    void t35() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt(); // 酒店个数
        int k = in.nextInt(); // 挑选酒店个数
        int x = in.nextInt(); // 心里预期值
        int[] data = new int[n];
        ArrayList<Integer> res = new ArrayList<>();
        int left = 0, right = 0, min = Integer.MAX_VALUE; // 左右指针
        for (int i = 0; i < n; i++) {
            data[i] = in.nextInt();
        }
        Arrays.sort(data);

        // 心里预期最近的那一个
        for (int i = 0; i < data.length; i++) {
            if (Math.abs(data[i] - x) < min) {
                left = i;
                right = i;
                min = Math.abs(data[i] - x);
            }
        }
        res.add(data[left]);
        k--;
        while (k != 0) {
            // 向左右扩散
            if (left == 0) { // 左端点情况
                res.add(data[++right]);
            } else if (right == n - 1) { // 右端点情况
                res.add(data[--left]);
            } else {
                if (Math.abs(data[left - 1] - x) <= Math.abs(data[right + 1] - x)) {
                    res.add(data[--left]);
                } else {
                    res.add(data[++right]);
                }
            }
            k--;
        }
        Collections.sort(res);
        for (Integer integer : res) {
            System.out.print(integer + " ");
        }
    }

    /*
     * 寻找密码
     */
    void t37() {
        Scanner in = new Scanner(System.in);
        String[] dp = in.nextLine().split(" ");
        Set<String> set = new HashSet<>();
        String res = "";
        for (String string : dp) {
            set.add(string);
            for (int i = 0; i < string.length(); i++) {
                String tem = string.substring(0, i + 1);
                if (set.contains(tem)) {
                    if (i + 1 > res.length()) {
                        res = tem;
                    } else if (i + 1 == res.length() && tem.hashCode() > res.hashCode()) {
                        res = tem;
                    }
                } else {
                    break;
                }
            }
        }
        System.out.println(res);
    }

    /*
     * AI处理器
     */
    void t43() {
        Scanner in = new Scanner(System.in);
        int[] data = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int n = in.nextInt();
        int[] info = new int[2];
        for (int i = 0; i < data.length; i++) {
            if (data[i] <= 3) {
                info[0]++;
            } else {
                info[1]++;
            }
        }
        List<List<Integer>> dp = new ArrayList<>();
        List<List<Integer>> res = new ArrayList<>();
        dp.add(Arrays.asList(1, 3, 2, 4));
        dp.add(Arrays.asList(2, 4, 3));
        dp.add(Arrays.asList(4));
        dp.add(Arrays.asList(8));
        int t = 0;
        while (n != 1) {
            t++;
            n /= 2;
        }
        n = (int) Math.pow(2, t);
        for (int i = 0; i < dp.get(t).size(); i++) {
            if (dp.get(t).get(0) == 8) {
                if (data.length == 8) {
                    System.out.println(data.toString());
                } else {
                    System.out.println("[]");
                }
            } else {
                for (int j = 0; j < info.length; j++) {
                    if (dp.get(t).get(i) == info[j]) {
                        System.out.println();
                    }
                }
            }
        }

    }

    /*
     * 字符串重新排序
     */
    void t47() {
        Scanner in = new Scanner(System.in);

        String[] tems = in.nextLine().split(" ");
        Map<String, Integer> map = new HashMap<>();

        for (int i = 0; i < tems.length; i++) {
            char[] temc = tems[i].toCharArray();
            Arrays.sort(temc);
            String tem = String.valueOf(temc);
            map.put(tem, map.getOrDefault(tem, 0) + 1);
        }

        List<Map.Entry<String, Integer>> list = new ArrayList<>(map.entrySet());

        list.sort((a, b) -> {
            if (b.getValue() < a.getValue()) {
                return -1;
            } else if (b.getValue() == a.getValue()) {
                if (b.getKey().length() > a.getKey().length()) {
                    return -1;
                } else if (b.getKey().length() == a.getKey().length()) {
                    return a.getKey().hashCode() - b.getKey().hashCode();
                }
            }
            return 1;
        });

        String res = "";
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < list.get(i).getValue(); j++) {
                res += list.get(i).getKey() + " ";
            }
        }
        System.out.println(res.substring(0, res.length() - 1));
    }

    /*
     * MVP争夺战
     */
    void t48() {
        Scanner in = new Scanner(System.in);
        // in.nextLine();
        int[] data = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        Arrays.sort(data);
        int sum = Arrays.stream(data).sum();
        int min = Arrays.stream(data).max().getAsInt();

        for (int i = min; i <= sum; i++) {
            if (sum % i == 0) {
                int k = sum / i;
                int[] bucket = new int[k];
                if (dfs(data, 0, bucket, k, i))
                    System.out.println(i);
                return;
            }
        }
        System.out.println(-1);
    }

    boolean dfs(int[] nums, int index, int[] bucket, int k, int target) {
        // 结束条件优化
        if (index == nums.length)
            return true;
        for (int i = 0; i < k; i++) {
            // 优化点二
            if (i > 0 && bucket[i] == bucket[i - 1])
                continue;
            // 剪枝
            if (bucket[i] + nums[index] > target)
                continue;
            bucket[i] += nums[index];
            if (dfs(nums, index + 1, bucket, k, target))
                return true;
            bucket[i] -= nums[index];
        }
        return false;
    }

    /**
     * 不含101的数
     */
    void p1() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        int res = 0;
        for (int i = n; i <= m; i++) {
            String tem = Integer.toBinaryString(i);
            if (!tem.contains("101"))
                res++;
        }
        System.out.println(res);
    }

    /*
     * 取出最少的球
     */
    void p2() {
        Scanner in = new Scanner(System.in);
        int count = in.nextInt();
        int m = in.nextInt();
        int[] dp = new int[m];

        int sum = 0, index;
        boolean flag = true;
        for (int i = 0; i < m; i++)
            dp[i] = in.nextInt();

        for (int i = 0; i < dp.length; i++) {
            sum += dp[i];
            if (sum > count) {
                flag = false;
                break;
            }
        }
        if (flag) {
            System.out.println("[]");
        } else {
            sum = 0;
            for (index = count / m; count > sum; index++) {
                sum = 0;
                for (int j = 0; j < dp.length; j++) {
                    sum += dp[j] < index ? dp[j] : index;
                }
                if (sum > count)
                    break;
            }
            for (int i = 0; i < dp.length; i++) {
                dp[i] -= (index - 1) > dp[i] ? dp[i] : (index - 1);
            }
            for (int i : dp) {
                System.out.print(i + " ");
            }
        }
    }

    /*
     * 
     */
    void p24() {
        char[][] data = {
                { 'a', 'b', 'c' },
                { 'd', 'e', 'f' },
                { 'g', 'h', 'i' },
                { 'j', 'k', 'l' },
                { 'm', 'n', 'o' },
                { 'p', 'q', 'r' },
                { 's', 't' },
                { 'u', 'v' },
                { 'w', 'x' },
                { 'y', 'z' }
        };

        Scanner in = new Scanner(System.in);
        String str = in.nextLine();
        String turn = in.nextLine();

        List<String> dp = new ArrayList<>();
        for (int i = 0; i < str.length(); i++) {
            addstr(dp, data[Integer.parseInt(str.substring(i, i + 1))]);
        }

        for (String string : dp) {
            if (check(string, turn)) {
                System.out.print(string + ",");
            }
        }
        System.out.println();
    }

    boolean check(String a, String b) {
        for (int i = 0; i < b.length(); i++) {
            if (a.contains(b.substring(i, i + 1)))
                return false;
        }
        return true;
    }

    void addstr(List<String> dp, char[] data) {
        List<String> tem = new ArrayList<>();
        if (dp.isEmpty()) {
            for (int i = 0; i < data.length; i++) {
                dp.add(String.valueOf(data[i]));
            }
        } else {
            for (String string : dp) {
                for (int i = 0; i < data.length; i++) {
                    tem.add(string + data[i]);
                }
            }
            dp.clear();
            dp.addAll(tem);
        }
    }

    /*
     * 天然蓄水池
     */
    void p34() {
        Scanner in = new Scanner(System.in);
        int[] heights = Arrays.stream(in.nextLine().split(" ")).mapToInt(Integer::parseInt).toArray();
        int res = 0, left = 0, right = heights.length - 1, max_left = 0, max_right = 0;
        while (left != right) {
            int tem = 0, min = Math.min(heights[left], heights[right]);
            for (int i = left + 1; i < right; i++) {
                tem += heights[i] < min ? min - heights[i] : 0;
            }
            if (tem >= res) {
                res = tem;
                max_left = left;
                max_right = right;
            }

            if (heights[left] == heights[left + 1]) {
                left++;
            } else if (heights[right] == heights[right - 1]) {
                right--;
            } else {
                if (heights[left] < heights[right])
                    left++;
                else
                    right--;
            }
        }
        if (res == 0)
            System.out.println(0);
        else
            System.out.println(max_left + " " + max_right + ":" + res);
    }

    /*
     * 红黑图 迭代 二进制串
     */
    void p36() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int m = in.nextInt();
        List<int[]> data = new ArrayList<>();
        for (int i = 0; i < m; i++) {
            data.add(new int[] { in.nextInt(), in.nextInt() });
        }
        int time = (int) Math.pow(2, n);
        int res = 0;
        for (int i = 0; i < time; i++) {
            int[] tem = new int[n];
            boolean flag = true;
            int t = i;
            for (int j = n - 1; j >= 0; j--) {
                tem[j] = t % 2;
                t /= 2;
            }
            for (int[] j : data) {
                if ((tem[j[0]] == 1) && (tem[j[1]] == 1)) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                res++;
            }
        }
        System.out.println(res);
    }
}

class task {
    int id;
    int type;

    public task(int a, int b) {
        id = a;
        type = b;
    }
}

class node {
    int val;
    int next;

    public node(int a, int b) {
        val = a;
        next = b;
    }
}

public class OD {
    public static void main(String[] args) {
        Problem s = new Problem();
        // s.num();
        s.t48();
        // System.out.println((new Random().nextInt() % 100) < 60 ? "YES" : "NO");
    }
}
