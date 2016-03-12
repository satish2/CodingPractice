#include<stdio.h>
typedef struct 
{
	char id[13];
	char name[10];
	int totime;
	int q1time;
	int q2time;
	int q3time;
}std1;
int main()
{
	
	int i,n;
	std1 stdt[3];
	FILE *fp;
//	char filename[10];
//	printf("enter filename in which details are stored");
//	scanf("%s","1");
	fp = fopen("1.txt","r"); 
	for(i=0;i<3;i++)
	{
		fscanf(fp,"%s\t  %s\t  %d\t  %d\t  %d\t   %d",stdt[i].id,stdt[i].name,&stdt[i].totime,&stdt[i].q1time,&stdt[i].q2time,&stdt[i].q3time);
	}
	for(i=0;i<3;i++)
	{
		printf("%s  %s  %d  %d  %d   %d \n",stdt[i].id,stdt[i].name,stdt[i].totime,stdt[i].q1time,stdt[i].q2time,stdt[i].q3time);
	}
fclose(fp);
}