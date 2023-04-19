package Competition;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class DayProblem {

    // 2023.4.14 驼峰式匹配
    // queries = ["FooBar","FooBarTest","FootBall","FrameBuffer","ForceFeedBack"],
    // pattern = "FoBa"
    // 输出：[true,false,true,false,false]
    public List<Boolean> camelMatch(String[] queries, String pattern) {
        // List<Boolean> res = new ArrayList<>();

        // for (int i = 0; i < queries.length; i++) {
        // int a = 0, b = 0;
        // String query = queries[i];
        // boolean flag = true;

        // while (a != query.length() && b != pattern.length()) {
        // if (Character.isUpperCase(query.charAt(a)) &&
        // Character.isUpperCase(pattern.charAt(b))) {
        // if (query.charAt(a) != pattern.charAt(b)) {
        // flag = false;
        // break;
        // }
        // a++;
        // b++;
        // } else if (!Character.isUpperCase(query.charAt(a)) &&
        // !Character.isUpperCase(pattern.charAt(b))) {
        // if (query.charAt(a) == pattern.charAt(b)) {
        // b++;
        // }
        // a++;
        // } else if (Character.isUpperCase(query.charAt(a)) &&
        // !Character.isUpperCase(pattern.charAt(b))) {
        // flag = false;
        // break;
        // } else if (!Character.isUpperCase(query.charAt(a)) &&
        // Character.isUpperCase(pattern.charAt(b))) {
        // a++;
        // }
        // }
        // if (b == pattern.length()) {
        // for (; a < query.length(); a++) {
        // if (Character.isUpperCase(query.charAt(a))) {
        // res.add(false);
        // break;
        // }
        // }
        // if (a == query.length()) {
        // res.add(true);
        // }
        // } else {
        // res.add(false);
        // }
        // }
        // return res;
        int n = queries.length;
        List<Boolean> res = new ArrayList<Boolean>();
        for (int i = 0; i < n; i++) {
            boolean flag = true;
            int p = 0;
            for (int j = 0; j < queries[i].length(); j++) {
                char c = queries[i].charAt(j);
                if (p < pattern.length() && pattern.charAt(p) == c) {
                    p++;
                } else if (Character.isUpperCase(c)) {
                    flag = false;
                    break;
                }
            }
            if (p < pattern.length()) {
                flag = false;
            }
            res.add(flag);
        }
        return res;
    }

    // 2023.4.15 不邻接植花
    public int[] gardenNoAdj(int n, int[][] paths) {
        // 建图
        List<Integer> g[] = new ArrayList[n];
        Arrays.setAll(g, e -> new ArrayList<>());
        for (var e : paths) {
            int x = e[0] - 1, y = e[1] - 1; // 编号改从 0 开始
            g[x].add(y);
            g[y].add(x); // 建图
        }
        var color = new int[n];
        for (int i = 0; i < n; ++i) {
            var used = new boolean[5];
            for (var j : g[i])
                used[color[j]] = true;
            while (used[++color[i]]);
        }
        return color;
    }

    public static void main(String[] args) {
        String[] queries = { "FooBar", "FooBarTest", "FootBall", "FrameBuffer", "ForceFeedBack" };
        String pattern = "FoBaT";
        DayProblem d = new DayProblem();
        System.out.println(d.camelMatch(queries, pattern).toString());
    }
}
