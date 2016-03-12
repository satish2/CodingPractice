package satish.dynamicProgramming;

import java.util.Scanner;

public class CutRodMemoization {

	public static void main (String[] args){
		int[] prices = {1,5,8,9,10,17,17,20,24,30};

		Scanner reader = new Scanner(System.in);
		System.out.print("Enter total length of rod: ");
		int N = reader.nextInt();
		int[] optimal = new int[N];
		int[] pieces = new int[N];
		for(int i=0;i<N;i++){
			optimal[i] = -100;
			pieces[i] = -100;
		}
		int optimalTotalCost = CutRod(prices,N,optimal,pieces);
		System.out.println(optimalTotalCost);
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
	
	public static int CutRod(int[] prices, int N, int[] optimal,int[] pieces){
		int cost= -100;
		if(N == 0)
			return 0;
		
		if(optimal[N-1] != -100)
			return optimal[N-1];
		
		for (int i=1; i<=N; i++){
			int costWithCutting = prices[i-1] + CutRod(prices,N-i,optimal,pieces);
			if(costWithCutting > cost){
				cost = costWithCutting;
				pieces[N-1] = i;
			}
		}
		
		optimal[N-1] = cost;
		return cost;
		
	}
}
