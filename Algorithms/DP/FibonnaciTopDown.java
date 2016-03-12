package satish.dynamicProgramming;

import java.util.Scanner;
/*
 * Returns Fibonacci sequence till N (includes).
 */
public class FibonnaciTopDown {

	public static Integer[] fibonacciNumbers;

	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);
		System.out.print("Enter N, till where fibonacci series has to obtained:");
		Integer N = in.nextInt();
		fibonacciNumbers = new Integer[N+1];
		Fibonacci(N);
		printSeries();
	}

	public static void printSeries() {
		for (int i : fibonacciNumbers) {
			System.out.println(i);
		}
	}

	public static Integer Fibonacci(Integer N) {
		if (N == 0) {
			fibonacciNumbers[0] = 0;
			return 0;
		} else if (N == 1) {
			fibonacciNumbers[1] = 1;
			return 1;
		} else if (fibonacciNumbers[N] != null && fibonacciNumbers[N] != 0)
			return fibonacciNumbers[N];
		else
			fibonacciNumbers[N] = Fibonacci(N - 1) + Fibonacci(N - 2);
		return fibonacciNumbers[N];
	}
}
