import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int A[] = new int[N];
        int squares[] = new int[N];
        for(int A_i=0; A_i < N; A_i++){
            A[A_i] = in.nextInt();
            squares[A_i] = A[A_i]*A[A_i];
        }
        Boolean fr = false;
        int right=0,acute=0,obtuse=0;
        for(int i=0;i<=N-3;i++){
            for(int j=i+1;j<=N-2;j++){
                fr = false;
                for(int k=j+1;k<=N-1;k++){
                    if(A[i] + A[j] <= A[k]){
                        break; //need to take different A[j]
                    }
                    int a = squares[i];
                    int b = squares[j];
                    int c = squares[k];
                    if(a + b == c){
                        fr = true;
                        right++;
                    } else if(a + b > c){
                        acute++;
                    } else
                        obtuse++;
                } 
            }
        }
        System.out.println(acute+" " + right+ " " + obtuse);
        // your code goes here
    }
}


