#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
/*
 * Create a child process and both parent & child writes to a file. 
 * It can be observed that child gets same file descriptors of parent. But,
 * when child closes file, filedes in parent is not closed. 
 * These file descriptors are local to each file.
 * File descriptors are nothing but references (Pointers) to inodes. 
 */

int main(int argc, char *argv[]){
	
	int f = open("f2.txt",O_CREAT|O_RDWR|O_TRUNC,S_IRWXU);
	printf("%d\n",f);
	char *str = "hello";
	int c_pid = fork();
	if(c_pid == 0){
		write(f, str, strlen(str));
		return;
	} else {
		write(f, str, strlen(str));
	}
	fsync(f);
	printf("Current Process = %d\n",(int)getpid());
	int count = 2*strlen(str)+1;
	char *data = (char *)calloc(count,sizeof(char));
	lseek(f, 0, SEEK_SET);
	int ret = read(f,(void *)data,count);
	if(ret == -1){
		printf("%m\n");
	}
	data[count] = '\0';
	printf("Contents = %s\n",data);
}
