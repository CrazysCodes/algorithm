package HS.test3;

import java.util.Scanner;

public class test {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int res = b - a + 1;
        for (int i = a; i <= b; i++) {
            for (int j = 2; j < i; j+=2) {
                if (i % j == 0) {
                    res--;
                    break;
                }
            }
        }
        System.out.println(res);
    }
}