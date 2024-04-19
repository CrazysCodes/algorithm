package HS.test1;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        char c = line.charAt(0);
        System.out.print(c);
        int count = 1;
        for (int i = 1; i < line.length(); i++) {
            if (c == line.charAt(i)) {
                count++;
            } else {
                if (count != 1) System.out.print(count);
                c = line.charAt(i);
                System.out.print(c);
                count = 1;
            }
        }
        if (count != 1) System.out.println(count);
    }
}
