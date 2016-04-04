#include <stdio.h>
#include <stdlib.h>

void modify(int **arr_addr){
	int *temp = *arr_addr;
	printf("before modify = %d\n",**arr_addr);
	temp = temp+9;
	*arr_addr = temp;
	printf("modify = %d\n", **arr_addr);
}

void print(int *arr){
	printf("print = %d\n",*arr);
}

void main(){
	int *array = (int *)malloc(sizeof(int)*10);
	int i = 1;
	while(i <= 10){
		array[i] = i;
		i++;
	}
	modify(&array);
	print(array);
}
