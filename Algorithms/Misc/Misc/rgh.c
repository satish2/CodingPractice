//reading inputs from file
/*
TO SOLVE MYSTERY OF HOW TO PAUSE ALL PROCESSES AND INVOKE ALL PROCESSES AT SAME TIME AND LET PARENT WAIT TILL ALL CHILDREN COMPLETE ALL THEIR PROCESSES.
*/
#include<stdio.h>
#include<unistd.h>
#include<errno.h>
#include <sys/types.h>
typedef struct 
{
	int id;
	char name[10];
	int totime;
	int q1time;
	int q2time;
	int q3time;
}std1;
//globalising variables ???
int p[100],q[100],r[100];
int main()
{
	
//initialize all arrays to zeros	
	FILE *fp;
	int i,j; 
	char filename[10];
	printf("enter total number of students");
	scanf("%d",&n);
	pid_t pid[n];
	pid_t p[n];
	std1 stdt[n];
//reading data from file	
	printf("enter filename in which details are stored");
	scanf("%s",filename);
	fp=fopen(filename,"r");
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%s  %s  %d  %d  %d   %d",stdt[i].id,stdt[i].name,&stdt[i].totime,&stdt[i].q1time,&stdt[i].q2time,&stdt[i].q3time);
	}
	fclose(fp);
for(i=0;i<n;i++)
{
   if(stdt[i].totime > stdt[i].q1time)
   {
        p[i]=1;
     if(stdt[i].totime > (stdt[i].q1time+stdt[i].q2time))
     {
   	  q[i]=1;
   	  if(stdt[i].totime > (stdt[i].q1time+stdt[i].q2time+stdt[i].q3time))
   	  {
   	  		r[i]=1;
   	  }
     }    	
	}
}		
for(i=0;i<n;i++)
	{
		p=fork();
		if(p==0)
		{
			pid[i]=getpid();
			//pause processes may be using exit(); MAY BE USING SIGTSTP OR SIGSTOP
		
		}
	}	

/*this is after a process is invoked
while comparing 'i' is choosen based on invoked process' pid
compare pid
now invoke all processes simultaneously and take care parent do not access these lines...
*/
kill(-1,SIGCONT);//INVOKES ALL PROCESSES
if(p==0)	//for allowing only child
{
      /*below lines must be done by student[i] process....
      
      ? how to access p[i] from child side ..... 
      */
      //checking which process is activated.. ??? is pid's value get's same even after pausing and waking process in between
for(i=0;i<n;i++)
{      
      	if(pid[i]==getpid())
      {	
      /*	i=j; */
      //(or)
      
      //check for 3ques
         if(p[i]+q[i]+r[i] == 3)
         {
         	fork1();
         	if(!fork2())
         	{
         			 	if(!forsk3())
         			 	{
         				 	printf("done 3 ques");
         				 	 exit();
         				 }	
         	exit();
         	}
         	exit();
         }
         //check for 2ques				 	
         else if(p[i]+q[i] == 2)
         {
         	fork1();
         	if(!fork2())
         	{
         			 	printf("done 2 ques");
         				exit();
            }	
         	exit();
         }
         //check for 1 ques
         else if(p[i] == 1)
         {
         	fork1();
         	exit();
         }
         else 
         {
         	printf("none is done");
         } 
     }		//ending if(pid[i]==getpid())
}				//ending for loop
}				//ending if(p==0)
	return 0;
}


