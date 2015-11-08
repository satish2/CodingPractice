/*Write a program that creates a child process, and then in the child
closes standard output (STDOUT FILENO). What happens if the child
calls printf() to print some output after closing the descriptor?*/
/*
 * No output on screen. This is risky, could cause error! Do not use it. Better to open some file to which 
 * further writes can go to.
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[]){
	
	int c_pid = fork();
	int ret;
	if(c_pid == 0){
		close(1); //1 = STDOUT_FILENO
		ret = printf("hello");
		if(ret < 0){
		        char *myargs[3];
		        myargs[0] = strdup("wc");   // program: "wc" (word count)
		        myargs[1] = strdup("p4.c"); // argument: file to count
		        myargs[2] = NULL;           // marks end of array
		        execvp(myargs[0], myargs);  // runs word count	
		}
		} 
	ret = wait(NULL); // This vs file to wait for child!!
	printf("parent wait : %d\n",ret);
	printf("Goodbye!\n");
	return 0;
}
