//Extra Long factorials
#include <stdio.h>

int main(int argc, char *argv[]){
	
	int size = 200;
	int arr[200] = {0};
	arr[199] = 1;
	puts("Enter Number N for fact(N)");
	int N,i,j,carry=0;
	scanf("%d",&N);
	int m = 1;
	for(i=1; i<=N; i++){
		for(j=1;j<=m;j++){
			int temp = arr[size-j]*i + carry;
			arr[size-j] = temp%10;
			carry = temp/10;
		}
		while(carry > 0){
			m++;
			arr[size-m] = carry%10;
			carry = carry/10;
		}
	}
	for(i=size-m;i<=199;i++){
		printf("%d",arr[i]);
	}
	printf("\n");
}
