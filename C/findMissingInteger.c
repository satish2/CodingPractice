//find missing integer in ascending array
#include <stdio.h>
int findMissingInteger(int *arr, int st, int end){

	if(st > end) return -1;
	if(end - st == 1 ){
		if(arr[end] - arr[st] > end - st){
			return arr[st]+1;
		} else {
			printf("here\n");
			return arr[st]-1;
		}
	}

	int mid = (st + end)/2;
	if(arr[mid] - arr[0] > mid-0){
		return findMissingInteger(arr, st, mid);
	} else if(arr[end] - arr[mid] > (end - mid)) {
		return findMissingInteger(arr, mid, end);
//Can't have mid+1 here, then if 11 goes missing, ends up with subarray of size 1 where segfault happens
	} else
		return -1;
}


int main(int argc, char **argv){
	int array[] = {4,5,6,7,8,9,10,11,12,13,14};//10
	printf("missing integer is %d\n",findMissingInteger(array, 0, 9));
	return 0;
}
