package satish.dynamicProgramming;

import java.util.Scanner;

public class CutRodBottomUp {
	public static void main (String[] args){
		int[] prices = {1,5,8,9,10,17,17,20,24,30};
		System.out.print("Enter length of rod : ");
		Scanner reader = new Scanner(System.in);
		int N = reader.nextInt();
		int[] optimal = new int[N];
		int[] pieces = new int[N];
		for(int i=0;i<N;i++){
			optimal[i] = -100;
			pieces[i] = -100;
		}
		optimal[0] = 1;
		pieces[0] = 1;
		for(int i = 1; i<=N;i++){
			int cost = -100;
			for (int j = 1; j<=i; j++){
				if(i-j-1 < 0) {
					if(cost < prices[i-1]) {
						cost = prices [i-1];
						pieces[i-1] = i;
					}
				}
				else {
					if(cost < prices[j-1] + optimal[i-j-1]){
						cost = prices[j-1] + optimal[i-j-1];
						pieces[i-1] = j;
					}
				}
			}
			optimal[i-1] = cost;
		}
		System.out.println(optimal[N-1]);
		printPieces(pieces,N);
	}
	
	public static void printPieces(int[] pieces,int totalLength) {
		int pieceLength = pieces[totalLength-1];
		int remainingLength = totalLength - pieceLength;
		while (remainingLength >= 0) {
			System.out.print(pieceLength + "\t");
			if(remainingLength <= 0)
				break;
			pieceLength = pieces[remainingLength-1];
			remainingLength = remainingLength - pieceLength;
		}
	}
	
	public static int max(int a, int b){
		if (a > b)
			return a;
		else return b;
	}
}
