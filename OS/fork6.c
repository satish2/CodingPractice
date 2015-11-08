/*
 * http://stackoverflow.com/questions/24766013/is-it-really-necessary-to-close-the-unused-end-of-the-pipe-in-a-process
 * http://stackoverflow.com/questions/11599462/what-happens-if-a-son-process-wont-close-the-pipe-from-writing-while-reading
 * 
 * Two child processes communicate over a pipe.
 * Note:
 * 1.pipe pids must be created before fork, else child and parent will get different file descriptors 
 * which are of no use for parent-> child or child->child communication as one cannot access the other.
 * 
 * 2.Parent must close both read and write ends of pipe if it wants its children to communicate with eachother. 
 * Pipe write end must be closed or else read won't give EOF. Also, if the write end is not closed, then pipe buffer can be overflown,
 * thus, write will hang for reader to make space for further writes.
 * 
 * If read end is not closed, writer process cannot know if the reader process has ended or not. So, it is needed that unused ends of pipes are closed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE -1
#endif

#ifndef STDOUT_FILENO
#define STDOUT_FILENO 1
#endif

#ifndef STDIN_FILENO
#define STDIN_FILENO 0
#endif


int main(int argc, char *argv[]){


	int cpid[2] = {0};
	int ppid[2];
	int status = 0;	
	int ret = 0;
	if(pipe(ppid) == -1){
		printf("Pipe creation failed\n");
		printf("%m");
		return -1;
	}
	cpid[0] = fork();
	if(cpid[0] == 0){
		close(ppid[0]);
		char *str = (char *) calloc(20,sizeof(char));
		if(str == NULL){
			fprintf(stderr, "could not create char array for string\n");
			exit(1);
		}
		strcpy(str,"hello hello!!\n");
		ret = write(ppid[1],(void *)str,20); 
		free(str);
		if(ret < 0){
			perror("__write failed\n");	
			exit(1);
		}
		exit(0);
	} else if (cpid[0] < 0 ) {
		printf("Error occured while creating writer\n");
		return -1;
	}
	else {
		waitpid(cpid[0],&status,0);
		printf("Child 0 exited with status = %d\n", status);
		if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
	        } else if (WIFSIGNALED(status)) {
	                printf("killed by signal %d\n", WTERMSIG(status));
	        } else if (WIFSTOPPED(status)) {
	                printf("stopped by signal %d\n", WSTOPSIG(status));
	        } else if (WIFCONTINUED(status)) {
        	        printf("continued\n");
	        }
		cpid[1] = fork();
		if(cpid[1] < 0 ){
			printf("Creation of second child failed\n");
			return -1;
		}
		if(cpid[1] == 0){
			close(ppid[1]);
			char *temp = (char *)calloc(15,sizeof(char));
			ret = read(ppid[0],temp,15);//read(STDIN_FILENO,temp,15);
			if(ret < 0) {
				printf("read failed");
			} else {
				printf("read success %d\n", ret);
			}
			write(STDOUT_FILENO,temp,15);
			exit(EXIT_SUCCESS);			
		}
	}
	close(ppid[0]);
	close(ppid[1]);
	waitpid(cpid[1],&status,0);
	printf("Child 1 exited with status = %d\n",status);
	exit(0);
}
