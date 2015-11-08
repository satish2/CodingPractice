#include <stdio.h>
#include <stdlib.h>

int solve(int org, int st);
int maxOf(int, int, int);

int *solve_value;
int *donations;
int size;

int maxOf(int a, int b, int c){
	int max = -1000000;
	if(a > max)
		max = a;
	if(b > max)
		max = b;
	if(c > max)
		max = c;
	return max;
}

int solve(int org, int st){
	if(st == org || (st+1)%size == org || st%size == (org+1))
		return 0;
	printf("org = %d, st = %d\n", org, st);
	int i = st; 
	int val = 0, max = -1000000;
	for(; (i%size) != 0; i++){
		printf("in for loop org = %d, st = %d, val =%d, i=%d\n", org, st, val, i);
		if((i+1)%size == org || org+1 == i%size)
			continue;
		val = donations[i] + solve(org,(st+2)%size);
		if(val > max)
			max = val;
	}
	if(max != -1000000)
		solve_value[st] = max;
	return solve_value[st];
}

int main(int argc, char *argv[]){

	int i=0;
	scanf("%d",&size);
	donations = (int *)calloc(size, sizeof(int));
	solve_value = (int *)calloc(size, sizeof(int));
	for(i=0;i<size;i++){
		scanf("%d",&donations[i]);
	}
	int ret1 = donations[0] + solve(0 , (0+2)%size);
	printf("dne ret1\n");
	int ret2 = donations[1] + solve(1 , (1+2)%size);
	int ret3 = donations[size-1] + solve(size-1 ,1);
	printf("%d\n",maxOf(ret1, ret2, ret3));
	return 0;
}
