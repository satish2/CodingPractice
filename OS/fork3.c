/*
Write a slight modification of the previous program, this time using
waitpid() instead of wait(). When would waitpid() be
useful?
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char *argv[]){
	
	int c_pid = fork();
	int ret;
//	unlink("f3.txt");
//	int f = open("f3.txt",O_RDWR | O_CREAT,S_IRWXU);
	if(c_pid == 0){
//		lseek(f, 0, SEEK_SET);
		printf("Hello \n");
//		write(f, "1",1);
		ret = wait();
		printf("child = %d wait : %d\n",(int) getpid(), ret);
		return 0;
	} 
//	int ret = fsync(f);
//	if(ret == -1) printf("%m");
//	char *temp = (char *)calloc(2,sizeof(char));
/*	while(1){
		lseek(f, 0, SEEK_SET);
		int ret = read(f, (void *)temp, 2);
		if(ret == -1)
			printf("%m");
		temp[1] = 0;	
		printf("%c",temp[0]);
		if(temp[0] == '1'){
			printf("%s",temp);
			break;
		}
	}*/
	ret = wait(NULL); // This vs file to wait for child!!
	printf("parent wait : %d\n",ret);
	printf("Goodbye!\n");
//	free(temp);
	return 0;
}
