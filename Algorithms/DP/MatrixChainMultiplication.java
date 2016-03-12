package satish.dynamicProgramming;

import java.util.Scanner;

public class MatrixChainMultiplication {
	private static final Integer HUGE = 2147483647;//largest Integer supported my Java

	public static void main(String[] args) {
		Scanner reader = new Scanner(System.in);
		System.out.print("Enter A, which indicates start matrix: ");
		Integer A = reader.nextInt();
		System.out.print("Enter B, which indicates end matrix: ");
		Integer B = reader.nextInt();
//		Integer[][] listOfMatricesOrders = { { 30, 35 }, { 35, 15 }, { 15, 5 }, { 5, 10 }, { 10, 20 }, { 20, 25 } };
		Integer[][] listOfMatricesOrders = getListOfMatrixOrders();
		Integer optimal[][] = new Integer[B][B]; // m <-- contains optimal cost[no.of
											// scalar multiplications] in ixj
											// multiplication
		Integer parenthesized[][] = new Integer[B][B]; // s <-- contains k, at which ixj
											// must be parenthesized to obtain
											// optimal solution
		for (int i = 0; i < B; i++)
			optimal[i][i] = 0; 

		getOptimal(optimal, parenthesized, listOfMatricesOrders,A, B);
	}

	static void getOptimal(Integer[][] optimal, Integer[][] parenthesized, Integer[][] listOfMatricesOrders, Integer startMatrix, Integer endMatrix) {
		int chainLength = 2; // chainLength i.e., [no.of.matrices multiplied
								// together] increments from 2 to N;
		for (; chainLength <= endMatrix; chainLength++) {
			for (int i = (startMatrix -1),j = i + chainLength - 1; i < endMatrix - chainLength+1; i++, j++) {
				int cost;
				optimal[i][j] = HUGE; 
				for (int k = i; k < j; k++) {
					cost = optimal[i][k] + optimal[k + 1][j] + listOfMatricesOrders[i][0] * listOfMatricesOrders[k][1] * listOfMatricesOrders[j][1];
					if (cost < optimal[i][j]) {
						optimal[i][j] = cost;
						parenthesized[i][j] = k+1;
					}
				}
			}
		}
		
		System.out.println("\n Total no of scalar multiplications = " + optimal[startMatrix-1][endMatrix-1]);
		System.out.println(printOptimalParenthesis(parenthesized,startMatrix,endMatrix));
	}
	
	static String printOptimalParenthesis(Integer[][] parenthesized, int startMatrix,int endMatrix){
		if(startMatrix == endMatrix)
			return ""+startMatrix;
		else
			return ("(" + printOptimalParenthesis(parenthesized, startMatrix, parenthesized[startMatrix-1][endMatrix-1]) + 
					printOptimalParenthesis(parenthesized, parenthesized[startMatrix-1][endMatrix-1]+1, endMatrix)+")");
	}
	
	static Matrix optimalMatrixMultiply(Matrix[] listOfMatrices,Integer[][] parenthesized, int startMatrix,int endMatrix){

		if(endMatrix - startMatrix == 1){
			return multiplyMatrices(listOfMatrices[startMatrix-1],listOfMatrices[endMatrix-1]);
		} else {
			return multiplyMatrices(optimalMatrixMultiply(listOfMatrices,parenthesized,startMatrix,parenthesized[startMatrix-1][endMatrix-1]),
					optimalMatrixMultiply(listOfMatrices,parenthesized,parenthesized[startMatrix-1][endMatrix-1]+1,endMatrix));
		}
	}
	
	static Matrix multiplyMatrices(Matrix A, Matrix B){
		if(A.columns != B.rows){
			System.out.print("Invalid Multiplication");
			return null;
		}else {
			Matrix C = new Matrix(A.rows,B.columns);
			for (int i=0;i < A.rows; i++){
				for (int j=0;j< B.columns;j++){
					for (int k=0;k< B.rows; k++){
						C.values[i][j] += A.values[i][k]*B.values[k][j];
					}
				}
			}
			return C;
		}
	}
	
	static Integer[][] getListOfMatrixOrders(){ //given a sequence, it constructs array similar to listofMatricesOrder in main method
		Scanner reader = new Scanner(System.in);
		System.out.println("\nEnter sequence :");
		String sequence = reader.nextLine();
		String[] orders = sequence.split("\\s");
		Integer[][] listOfMatricesOrders = new Integer[orders.length-1][2];
		for (int i=0;i<orders.length-1;i++){
			listOfMatricesOrders[i][0] = Integer.parseInt(orders[i]);
			listOfMatricesOrders[i][1] = Integer.parseInt(orders[i+1]);
		}
		return listOfMatricesOrders;
	}
}


class Matrix {
	int rows;
	int columns;
	Integer[][] values;
	
	public Matrix(int rows,int columns){
		this.rows = rows;
		this.columns = columns;
		this.values = new Integer[rows][columns];
	}
	
	public void enterMatrix(){
		System.out.println("Enter Matrix values:");
		Scanner reader = new Scanner(System.in);
		for(int i=0;i<rows;i++){
			for (int j=0;j<columns;j++){
				System.out.print("i = "+i + "j= "+j);
				values[i][j] = reader.nextInt();
				System.out.println();
			}
		}
	}
}

/*
 * CLRS - 15.2-4 {{1,2}, {2,3}, {3,4}.... {n-1,n}}
 * Nodes -> (1..1),(2..2),(3..3),....,(n..n) & (i..j) such that i < j & i = 1 -> n-1
 * Nodes in sub-problem graph = n + (n*(n-1)/2) = (n*(n+1)/2) <-- NUMBER OF ENTRIES IN OPTIMAL ARRAY.
 * Edges -> NUMBER OF ENTRIES IN PARENTHESIZED ARRAY -> edge exists between i & j with i < endMatrix & j <=endMatrix and i < j;   
 */
