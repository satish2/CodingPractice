#include <stdio.h>
#include <stdlib.h>
#define INTEGER_MIN (1<<31)
int r = 0, c = 0;
int findMax(int *countarr){
	int i=0, max = INTEGER_MIN;
	for(; i < 8; i++){
		if(countarr[i] > max) max = countarr[i];
	}
	return max;
}

int findAnswer(int **mat, int **visited, int i, int j, int count){
	if(i < 0 || i >= r) return count;
	if(j < 0 || j >= c) return count;
	int maxCount = INTEGER_MIN;
	if(visited[i][j] == 0 && mat[i][j] == 1){
		//for each neighbor (8-directions)
		printf("At Node mat[%d][%d] = %d, count = %d\n",i, j,mat[i][j],count);
		count++;
		visited[i][j] = 1;
		count = findAnswer(mat, visited, i-1, j, count);
		count = findAnswer(mat, visited, i+1, j, count);
		count = findAnswer(mat, visited, i, j-1, count);
		count = findAnswer(mat, visited, i, j+1, count);
		count = findAnswer(mat, visited, i-1, j-1, count);
		count = findAnswer(mat, visited, i-1, j+1, count);
		count = findAnswer(mat, visited, i+1, j-1, count);
		count = findAnswer(mat, visited, i+1, j-1, count);
	}
	return count;
}

void printMatrix(int **mat){
	int i = 0, j = 0;
	for(; i < r; i++){
		for(j=0;j<c;j++){
			printf("%d\t",mat[i][j]);
		}
		printf("\n");
	}
}	

int main(void) {
	// your code goes here
	printf("Enter Rows: ");
	scanf("%d",&r);
	printf("Enter Columns: ");
	scanf("%d", &c);
	int **mat = (int **)malloc(sizeof(int *)*r + sizeof(int)*r*c);
	int i = 0, j = 0;
	for(; i < r; i++){
		mat[i] = (int *)(mat + sizeof(int *)*r + sizeof(int)*c*i);
	}
	printf("\nEnter Matrix:\n");
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			scanf("%d",&mat[i][j]);
	int **visited = (int **)malloc(sizeof(int *)*r + sizeof(int)*r*c);
	for(i=0; i < r; i++){
		visited[i] = (int *)(visited + sizeof(int *)*r + sizeof(int)*c*i);
	}
	for(i=0;i<r;i++)
		for(j=0;j<c;j++)
			visited[i][j] = 0;
	printMatrix(mat);
	int max = INTEGER_MIN;
	int k = 0, l = 0;
	for(k = 0; k < r; k++){
		for(l = 0; l < c; l++){
			if(visited[k][l] == 0 && mat[k][l] == 1) {
				int temp = findAnswer(mat, visited, k, l, 0);
				if(max < temp) max = temp;
			}
		}
	}
	printf("Answer = %d\n", max);
	free(visited);
	free(mat);
	return 0;
}
