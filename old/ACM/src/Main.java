import java.util.*;

public class Main {
    public static void main(String[] args) {
        System.out.println(pow(2,8));
    }
    public static int pow(int a, int b){
        int res = 1;
        int base = a;
        while(b != 0){
            if((b&1) == 1){
                res = res * base;
            }
            base = base *base;
            b = b >> 1;
        }
        return res;
    }
    public static void srot(int [] array , int start,int end){
        int i = start,j = end;
        int target = array[start];
        while(i<j){
            while(i < j&& target <=array[j])    j--;
            if(i < j){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
            while(i < j && target >= array[i])  i++;
            if(i < j){
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
        if(i -1 > start){
            srot(array,start,i-1);
        }
        if(j + 1 < end){
            srot(array,j+1 ,end);
        }
    }
}