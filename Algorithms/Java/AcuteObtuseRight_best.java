import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    public static int binarySearch(int[] A, int st, int end, int val) {
		if (st >= end)
			return end;
		int mid = (st + end) / 2;
		if (A[mid] == val)
			return mid;
		else if (A[mid] < val)
			return binarySearch(A, mid + 1, end, val);
		else
			return binarySearch(A, st, mid, val);
	}
    
    public static int binarySearch_long(long[] A, int st, int end, long val) {
		if (st >= end)
			return end;
		int mid = (st + end) / 2;
		if (A[mid] == val)
			return mid;
		else if (A[mid] < val)
			return binarySearch_long(A, mid + 1, end, val);
		else
			return binarySearch_long(A, st, mid, val);
	}
    
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int N = in.nextInt();
        int A[] = new int[N];
        long squares[] = new long[N];
        for(int A_i=0; A_i < N; A_i++){
            A[A_i] = in.nextInt();
            squares[A_i] = A[A_i] * A[A_i];
        }
        long right = 0, acute = 0, obtuse = 0;
		for (int i = 0; i <= N - 3; i++) {
			for (int j = i + 1; j <= N-2; j++) {
				int k = j+1;
				if(A[i] + A[j] < A[k])
                    			continue;
                
				int sumEqualPos = binarySearch(A, k, N-1, A[i] + A[j]); 
				int squarePos = binarySearch_long(squares, k, sumEqualPos, squares[i]+ squares[j]); 

				acute += squarePos-k;

				if (squares[squarePos] < (squares[i] + squares[j])){
					squarePos++;
					acute ++;
				} else if (squares[squarePos] == (squares[i] + squares[j])){
					right ++;
					squarePos++;
				} 
				
				if(A[sumEqualPos] < A[i] + A[j]) sumEqualPos ++;
				if(squarePos < sumEqualPos)
					obtuse += sumEqualPos - squarePos;
			}
		}
		System.out.println(acute + " " + right + " " + obtuse);
        
    }
}

