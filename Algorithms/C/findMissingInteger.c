//find the missing integer
#include <stdio.h>

void findMissingInteger(int *arr, int length){
	int low = arr[0];
	int end = arr[length-1];
	
}

int main(int argc, char **argv){
	
	int arr = {1,2,3,4,5,5,6,7,9};
	findMissingInteger(arr, 9);
	return 0;
}
