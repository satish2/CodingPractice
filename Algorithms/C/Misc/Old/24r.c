#include<stdio.h>
#include<stdlib.h>
#define INFINITE 11111111
struct node
{
	int grey;
	int ancestor;
};
int floyd_warshall(int **);
int min(int a,int b);

int m,n;
int main()
{
	//using floyd-warshall algorithm

	int k,i,j,z,temp1,temp2;
	printf("enter 'm'\n");
	scanf("%d",&m);
	printf("enter 'n'\n");
	scanf("%d",&n);
	int a[m*n];
	int D[m*n][m*n];
	int PI[m*n][m*n];
	z = m*n;
	printf("enter greyscale along column and on reaching end of column then from next row accordingly\n");
	for(i=0;i<m*n;i++)
	{
			
			scanf("%d",&a[i]);
	}		
	for(i=0;i<z;i++)
	{
		for(j=0;j<z;j++)
		{
			if(i==j) D[i][j]=0;
			else if(j==i-1&& i%n !=0 || i==j-1&& i%n != n-1)
			{
				D[i][j] = a[i]+a[j];
				//printf("*/*/ i = %d j = %d D[i][j]=%d\n",i,j,D[i][j]);
			}
			else if(j == i+n || j == i-n)
			{
				D[i][j] = a[i]+a[j]; 
			//	printf("*/*/ i = %d j = %d D[i][j]=%d\n",i,j,D[i][j]);
			}
			else if(j == i+(n+1) && i%n != n-1|| j == i-(n-1)&& i%n != n-1)
			{
				D[i][j] = a[i]+a[j];
				//printf("*/*/ i = %d j = %d D[i][j]=%d\n",i,j,D[i][j]);
			}
			else if(j == i-(n+1) && i%n != 0 || j == i+(n-1) && i%n !=0)
			{  //printf("*/*/ i = %d j = %d \n",i,j);
				D[i][j] = a[i]+a[j];	
				//printf("*/*/ i = %d j = %d D[i][j]=%d\n",i,j,D[i][j]);
			}
			else 
			D[i][j] = INFINITE;
				//	printf(".............................D[%d][%d]=%d\n",i,j,D[i][j]);
		}
	}
		for(i=0;i<z;i++)
		{
			for(j=0;j<z;j++)
			{
				if(i==j||D[i][j]==INFINITE)PI[i][j]=0;
				else PI[i][j]=i;
	//			printf("PI[%d][%d]=%d \n",i,j,PI[i][j]);
			}
		}		
	
	for(k=0;k<z;k++)
	{
		for(i=0;i<z;i++)
		{
			for(j=0;j<z;j++)
			{
				if(i==j)PI[i][j]=0;
				else if(	D[i][j] >D[i][k]+D[k][j])
				PI[i][j]=PI[k][j];
				else 
				PI[i][j]=PI[i][j];
				D[i][j]=min(D[i][j],D[i][k]+D[k][j]); 
				//if(i==0 && j==5)printf(".,.,.,D[%d][%d]=%d k =%d\n",i,j,D[i][j],k);
				
			}				
		}
	}
/*	printf("done\n");
	for(i=0;i<z;i++)
		{
			for(j=0;j<z;j++)
			{
				printf("D[%d][%d]=%d \n",i,j,D[i][j]);
				
			}
		}	
		printf("\n\n\n");	
	
	for(i=0;i<z;i++)
		{
			for(j=0;j<z;j++)
			{
				//printf("PI[%d][%d]=%d \n",i,j,PI[i][j]);
				
			}
		}	*/
		printf("OUTPUT:\n");
		temp1=0;
		temp2=m*n-1;
		printf("%d %d\n",temp2/n+1,temp2%n+1);
		while(1)
		{
		i=PI[temp1][temp2];
		temp1=i/n;
		temp2=i%n;
		printf("%d %d\n",temp1+1,temp2+1);
		temp1=0;
		temp2=i;
		D[0][z-1]=D[0][z-1]-a[i];
		if(temp1 == 0 && temp2 ==0)
		break; 
		}
		printf("path is %d",D[0][z-1]) ;
	return 0;
}
int min(int a,int b)
{
	if(a>b)
	return b;
	else 
	return a;
}	
