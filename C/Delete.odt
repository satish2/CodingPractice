#include <stdio.h>
#include <stdlib.h>
int main(void) {
	// your code goes here
const int m=10, n=12; 
int (*ar)[m][n] = (int(*)[m][n]) malloc(sizeof(*ar)); 
//Access elements: 
int i =0, j = 0;
for(; i<m;i++){
	for(j=0;j<n;j++){
		(*ar)[i][j] = i+j;
	}
}

for(i=0; i<m;i++){
	for(j=0;j<n;j++){
		printf("%d\t", (*ar)[i][j]);
	}
	printf("\n");
}

// Free the memory. 
free(ar); ar = NULL; 
	return 0;
}

