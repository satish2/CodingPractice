#include<stdio.h>
int main()
{
	int i,j,k;
	char m;
	char a[3][13]={"2008a7ps011g","2008b3a3012g","2008a0ps014g"};
//sort by bucketing 1.branch.,2.id.,3.batch;
	char id[3][4];
	char bucket1[3][13]={"\0","\0","\0"};
	char bucket2[3][13]={"\0","\0","\0"};
	for (i=0;i<3;i++)
	{
		for(j=4;j<8;j++)
		{
			id[i][j]=a[i][j];
		}
	}
	
	for (i=0;i<3;i++)
	{
			if (id[i][4]=='a')
			{
					m=id[i][5];
					k=m;
					printf("%d %c \n",k,m);	
					bucket1[k]=a[k];
			}
			else 
			{
			
			
					bucket2[k]=a[k];
			}
	}		
	for (i=0;i<3;i++)
	{
		for(j=0;j<13;j++)
		{
			printf("%c",bucket1[i][j]);
		}
		printf("\n");
	}			

	

	return 0;
}	







/*	for (i=0;i<3;i++)
	{
		for(j=4;j<8;j++)
		{
			printf("%c\n",id[i][j]);
		}
	}	*/
//compare if last 2 chars are "ps" or not if one step and not other step..bucket for ps and different bucket for a*