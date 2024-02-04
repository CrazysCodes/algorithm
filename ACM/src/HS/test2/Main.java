package HS.test2;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int pointx = 0, pointy = 0, temp = 0, max = 0;
        int data[][] = new int[n][n];
        int res = 0;
        for (int i = 0; i < n; i++) {
            String line = sc.next();
            for (int j = 0; j < n; j++) {
                int a;
                a = line.charAt(j) == '0' ? 0 : 1;
                res += a;
                data[i][j] = a;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                temp += data[pointx][pointy];
                pointx++;
                pointy++;
                pointx %= n;
                pointy %= n;
            }
            if (temp == n) {
                System.out.println(res - n);
                return;
            }
            pointy = i;
            if (temp > max) max = temp;
            temp = 0;
        }
        res -= max;
        res += n - max;
        System.out.println(res);
    }
}
