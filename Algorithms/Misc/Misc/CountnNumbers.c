#include <stdio.h>
int main1(int argc, char **argv)
{
	int n,i, answer=0;
	printf("Enter how many numbers till you want to sum\n");
	scanf("%d", &n);
	for (i=1;i<=n;i++){
		answer = answer + i;
	}
	printf("answer = %d\n", answer);
	
	return 0;
}
