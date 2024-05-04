package HS.test6;

import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        int target = sc.nextInt();
        List<Node> list = new ArrayList<Node>();
        Node tree = new Node((sc.nextInt()));
        Node head = tree;
        int index = 2;
        for (int i = 2; i <= n; i++) {
            int temp = sc.nextInt();
            Node node;
            if(temp != -1){
                node = new Node(temp);
            }else {
                node = null;
            }
            list.add(node);
            if(n%2 == 0){
                tree.left = node;
            }else{
                tree.right = node;
                if(list.get(index/2) == null){
                    index++;
                    tree = list.get(index);
                }
            }
            index++;
        }
        while(head != null){
            System.out.println(head.val);
            head = head.left;
        }


    }

}
class Node{
    int val;
    Node left;
    Node right;

    public Node(int val) {
        this.val = val;
    }

    public int getVal() {
        return val;
    }

    public void setVal(int val) {
        this.val = val;
    }

    public Node getLeft() {
        return left;
    }

    public void setLeft(Node left) {
        this.left = left;
    }

    public Node getRight() {
        return right;
    }

    public void setRight(Node right) {
        this.right = right;
    }
}

