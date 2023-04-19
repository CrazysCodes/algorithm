package Code;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.Stack;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Map.Entry;

public class Main {
    public static void main(String[] args) {
        trob tro = new trob();
        System.out.println(tro.isvalid("]"));
    }
}

class trob {
    // ( ) [ ] { }
    public boolean isvalid(String s) {
        Stack<Character> sta = new Stack<>();
        Map<Character, Character> dp = new HashMap<>();
        dp.put(')', '(');
        dp.put(']', '[');
        dp.put('}', '{');

        if (s.length() % 2 != 0)
            return false;

        for (int i = 0; i < s.length(); i++) {
            char tem = s.charAt(i);
            if (tem != ')' && tem != ']' && tem != '}') {
                sta.push(tem);
            } else {
                if (sta.isEmpty() || sta.peek() != dp.get(tem)) {
                    return false;
                }
                sta.pop();
            }
        }
        if(!sta.isEmpty())
            return false;

        return true;
    }

    // 给定一个字符串，请将字符串里的字符按照出现的频率降序排列，若出现频次一样，按照先出现的后输出，例如输入tree，输出eert。并且在输入的字符串中大小写敏感。
    // tree -> eert
    String t(String str) {
        String res = "";
        Map<Character, Integer> dp = new HashMap<>();
        Map<Character, Integer> map = new HashMap<>();
        for (int i = 0; i < str.length(); i++) {
            if (!dp.containsKey(str.charAt(i))) {
                dp.put(str.charAt(i), i);
            }
            map.put(str.charAt(i), map.getOrDefault(str.charAt(i), 0) + 1);
        }

        List<Entry<Character, Integer>> list = new ArrayList<>(map.entrySet());
        list.sort((a, b) -> {
            if (a.getValue() < b.getValue()) {
                return 1;
            } else if (a.getValue() == b.getValue()) {
                if (dp.get(a.getKey()) < dp.get(b.getKey())) {
                    return 1;
                }
            }
            return -1;
        });
        for (Entry<Character, Integer> entry : list) {
            for (int i = 0; i < entry.getValue(); i++) {
                res += entry.getKey();
            }
        }

        return res;
    }
}