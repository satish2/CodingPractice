#include <stdio.h>

int main8(int argc,char** argv){
	
	int A[6] = {22,11,212,33,1,3};
	int i,j;
	
	for (j=1;j<6;j++){
		i = j-1;
		int key = A[j];
		while(i>=0 && A[i]<key){
			A[i+1]=A[i];
			i--;
		}
		A[i+1] = key;
	}
	for (j = 0; j< 6 ; j++ ) {
		printf("%d \t",A[j]);
		
	}
	return 0;
}