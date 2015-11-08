#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	
	int x = 100;
	int c_pid = fork();
	if(c_pid == 0){
		printf("Child: x = %d\n",x);
		x = 101;
	} else {
		printf("Parent: x = %d\n",x);
		x = 102;
	}
	printf("After Change : x = %d\n",x);
	return 0;
}
