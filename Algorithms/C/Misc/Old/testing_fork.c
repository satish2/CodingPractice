#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include<sys/types.h>
int main()
{
int i;
printf("fork program starting \n");
for(i=0;i<2;i++) {
    fork();
    printf("new process %d,parent of this is %d \n",getpid(),getppid());
}
return 0;
}
