//Hashtable

#include <stdio.h>
#define SIZE 100;
static int arr[100];

void put(int key, int value){
	int pos = hash(key);
	arr[pos] = value;
	return;
}

int get(int key){
	int pos = hash(key);
	return arr[pos];
}
