#include<stdio.h>
int main()
{
	float b1,b2,b3,a,b,c;
	int i;
	float a11,a12,a13,a21,a22,a23,a31,a32,a33;
	//assign values
	a=b=c=0;
	a11=-9;
	a12=7;
	a13=-20;
	a21=2;
	a22=-6;
	a23=3;
	a31=3;
	a32=-1;
	a33=1;
	b1=7;
	b2=-13;
	b3=4;
	float x1,x2,x3;
	x1=x2=x3=0;//initial values of X matrix..a,b,c, are x1,x2,x3 after one iteration...
	for(i=0;i<4;i++)
	{
		a=(b1-((a12*x2)+(a13*x3)))/(a11);
		b=(b2-((a21*x1)+(a23*x3)))/(a22);
		c=(b3-((a31*x1)+(a32*x2)))/(a33);
		printf("x1=%f \t x2=%f \t x3=%f \t",a,b,c);
		printf("\n");
		x1=a;
		x2=b;
		x3=c;
	}	
	 return 0;
} 
