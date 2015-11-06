/*
 * Write a program that creates two children, and connects the standard
output of one to the standard input of the other, using the
ipipe() system call.

If read end of pipe is closes, a write() will fail and process will be sent SIGPIPE signal. Default SIGPIPE handler terminates. 
 */

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
	//ppid[0] <-- reading end and ppid[1] is writing end
	if(cpid[0] == 0){
		close(ppid[0]);
		if(dup2(ppid[1],STDOUT_FILENO) != STDOUT_FILENO){
			fprintf(stderr, "failed to create dup of stdout");	
		}
		close(ppid[1]);
		char *str = (char *) calloc(20,sizeof(char));//"hello hello!!\n";
		if(str == NULL){
			fprintf(stderr, "could not create char array for string\n");
			exit(1);
		}
		strcpy(str,"hello hello!!\n");
		printf("hello satish how are you ? \n");
		//ret = write(STDOUT_FILENO,(void *)str,20); //write(STDOUT_FILENO,(void *)str,15);
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
		/*if (WIFEXITED(status)) {
			printf("exited, status=%d\n", WEXITSTATUS(status));
	        } else if (WIFSIGNALED(status)) {
	                printf("killed by signal %d\n", WTERMSIG(status));
	        } else if (WIFSTOPPED(status)) {
	                printf("stopped by signal %d\n", WSTOPSIG(status));
	        } else if (WIFCONTINUED(status)) {
        	        printf("continued\n");
	        }*/
		cpid[1] = fork();
		if(cpid[1] < 0 ){
			printf("Creation of second child failed\n");
			return -1;
		}
		if(cpid[1] == 0){
			//Child 2
			close(ppid[1]);
			if(dup2(ppid[0],STDIN_FILENO)){
				fprintf(stderr, "failed to create dup of stdin");
			}
			close(ppid[0]);
			//Now both ppid[0] and STDIN_FILENO refer stdin file description. So, both will have same file offset and status flags
			//Now I will close STDIN_FILENO i.e, remove reference from that variable and link it to ppid[0] i.,e reading end
			//Child 1 will read from now on, on this file descriptor.
			char *temp = (char *)calloc(100,sizeof(char));
			ret = read(STDIN_FILENO,temp,100);//read(STDIN_FILENO,temp,15);
			if(ret < 0) printf("read failed");
			write(STDOUT_FILENO,temp,100);
			exit(EXIT_SUCCESS);			
		}
	}
	close(ppid[0]);
	close(ppid[1]);
	waitpid(cpid[0],&status,0);
	waitpid(cpid[1],&status,0);
	exit(0);
}
