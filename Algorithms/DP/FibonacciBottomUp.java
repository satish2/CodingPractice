package satish.dynamicProgramming;

import java.util.Scanner;
/*
 * Returns fibonacci sequence till N (includes N)
 */
public class FibonacciBottomUp {
	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);
		System.out.print("Enter Integer N (N must be > 1) :");
		Integer N = in.nextInt();
		Integer[] fibonacciNumbers = new Integer[N+1];

		fibonacciNumbers[0] = 0;
		fibonacciNumbers[1] = 1;
		for (int j = 2; j <= N; j++) {
			fibonacciNumbers[j] = fibonacciNumbers[j - 1] + fibonacciNumbers[j - 2];
		}
		printSeries(fibonacciNumbers);
	}
	
	public static void printSeries(Integer[] fibonacciNumbers) {
		for (int i : fibonacciNumbers) {
			System.out.println(i);
		}
	}
}
