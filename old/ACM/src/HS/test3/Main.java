package HS.test3;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int a = sc.nextInt();
        int b = sc.nextInt();
        int res = b - a + 1;
        for (int i = a%2==0 ? a+1 : a ; i <= b; i += 2,res--) {
            for (int j = 2; j < i; j++) {
                if (i % j == 0) {
                    res--;
                    break;
                }
            }
        }
        System.out.println(res);
    }
}