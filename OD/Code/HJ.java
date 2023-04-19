package Code;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.regex.Pattern;

/**
 * 牛客网华为题库
 */

class solve {

    /**
     * 分割字符串
     */
    void t4() {
        Scanner in = new Scanner(System.in);

        while (in.hasNextLine()) {
            String a = in.nextLine();
            int i = 0;
            while (i < a.length() || i % 8 != 0) {
                if (i < a.length())
                    System.out.print(a.charAt(i));
                else
                    System.out.print(0);
                i++;
                if (i % 8 == 0)
                    System.out.println();
            }
        }
    }

    private final static int BASE = 16;
    private static Map<Character, Integer> map = new HashMap<Character, Integer>() {
        {
            put('0', 0);
            put('1', 1);
            put('2', 2);
            put('3', 3);
            put('4', 4);
            put('5', 5);
            put('6', 6);
            put('7', 7);
            put('8', 8);
            put('9', 9);
            put('A', 10);
            put('B', 11);
            put('C', 12);
            put('D', 13);
            put('E', 14);
            put('F', 15);
            put('a', 10);
            put('b', 11);
            put('c', 12);
            put('d', 13);
            put('e', 14);
            put('f', 15);
        }
    };

    /**
     * 进制转换
     */
    void t5() {
        Scanner in = new Scanner(System.in);

        String t = in.next();
        int b = 0, res = 0;
        for (int i = t.length() - 1; i > 1; i--) {
            res += map.get(t.charAt(i)) * Math.pow(BASE, b++);
        }
        System.out.println(res);
    }

    /**
     * 分解质因子
     */
    void t6() {
        Scanner in = new Scanner(System.in);
        int a = in.nextInt();
        for (int i = 2; i <= Math.sqrt(a); i++) {
            while (a % i == 0) {
                System.out.print(i + " ");
                a /= i;
            }
        }
        if (a > 1)
            System.out.print(a);
    }

    /**
     * 取近似值
     */
    void t7() {
        Scanner in = new Scanner(System.in);
        float a = in.nextFloat();
        if (a - (int) a >= 0.5)
            System.out.println((int) a + 1);
        else
            System.out.println((int) a);
    }

    /**
     * 合并表序列
     */
    void t8() {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        Map<Integer, Integer> m = new TreeMap<Integer, Integer>();
        for (int i = 0; i < t; i++) {
            int a = in.nextInt();
            if (m.containsKey(a))
                m.put(a, in.nextInt() + m.get(a));
            else
                m.put(a, in.nextInt());
        }
        for (int b : m.keySet())
            System.out.println(b + " " + m.get(b));
    }

    /**
     * 提取不重复的整数
     */
    void t9() {
        Scanner in = new Scanner(System.in);
        int t = in.nextInt();
        HashSet<Integer> s = new HashSet<Integer>();
        while (t > 0) {
            int a = t % 10;
            if (!s.contains(a)) {
                System.out.print(a);
                s.add(a);
            }
            t /= 10;
        }
    }

    /**
     * 字符个数统计
     */
    void t10() {
        Scanner in = new Scanner(System.in);
        String t = in.next();
        HashSet<Character> s = new HashSet<Character>();
        for (int i = 0; i < t.length(); i++)
            s.add(t.charAt(i));
        System.out.println(s.size());
    }

    /**
     * 字符串排序
     */
    void t14() {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        String[] array = new String[n];
        for (int i = 0; i < n; i++) {
            array[i] = in.next();
        }
        Arrays.sort(array);
        for (String str : array) {
            System.out.println(str);
        }
    }

    /**
     * 坐标移动
     */
    private static Map<Character, Integer> turn = new HashMap<Character, Integer>() {
        {
            put('A', -1);
            put('D', 1);
            put('W', -1);
            put('S', 1);
        }
    };

    void t17() {
        Scanner in = new Scanner(System.in);

        int x = 0;
        int y = 0;
        String a = in.nextLine();
        String[] data = a.split(";");
        for (String s : data) {
            // 不满足题目给定坐标规则
            if (!s.matches("[WASD][0-9]{1,2}")) {
                continue;
            }
            int val = Integer.valueOf(s.substring(1));
            switch (s.charAt(0)) {
                case 'W':
                    y += val;
                    break;
                case 'S':
                    y -= val;
                    break;
                case 'A':
                    x -= val;
                    break;
                case 'D':
                    x += val;
                    break;
            }
        }
        System.out.println(x + "," + y);
    }

    void t33() {
        Scanner in = new Scanner(System.in);
        String a = in.next();
        long b = in.nextLong();

        String[] d = a.split("\\.");

        long ra = 0, c = 3;
        for (String string : d)
            ra += Integer.parseInt(string) * Math.pow(256, c--);
        System.out.println(ra);

        c = 3;
        for (int i = 0; i < 3; i++) {
            System.out.print(b / Math.pow(256, c) + ".");
            c %= Math.pow(256, c--);
        }
        System.out.println(b);
    }

    /**
     * 称砝码
     */
    void t41() {
        Scanner in = new Scanner(System.in);
        HashSet<Integer> s = new HashSet<Integer>();
        List<Integer> l = new ArrayList<Integer>();
        List<Integer> tem = new ArrayList<Integer>();

        int t = in.nextInt();
        for (int i = 0; i < t; i++)
            l.add(in.nextInt());

        for (int i = 0; i < t; i++) {
            int count = in.nextInt();
            for (int j = 0; j < count - 1; j++)
                l.add(l.get(i));
        }
        Collections.sort(l);
        s.add(0);
        for (Integer integer : l) {
            for (Integer is : s)
                tem.add(is + integer);
            s.addAll(tem);
        }
        System.out.println(s.size());
    }

}

public class HJ {
    public static void main(String[] args) {
        solve s = new solve();

    }

}