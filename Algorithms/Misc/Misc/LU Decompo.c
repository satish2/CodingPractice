//LU decomposition;
//inverse of a matrix;
#include<stdio.h>
#include<conio.h>
int main()
{
	float a11,a12,a13,a21,a22,a23,a31,a32,a33;
	float l11,l12,l13,l21,l22,l23,l31,l32,l33;
	float u11,u12,u13,u21,u22,u23,u31,u32,u33;
	a11=1;
	a12=1;
	a13=0;
	a21=0;
	a22=1;
	a23=0;
	a31=0;
	a32=0;
	a33=0;
	u11=u22=u33=1;
	u21=u31=u32=0;
	l12=l13=l23=0;
	l11=a11;
	l21=a21;
	l31=a31;
	u11=a11/l11;
	u12=a12/l11;
	u13=a13/l11;
	l22=a22-(l21*u12);
	u23=(a23-(l21*u13))/l22;
	l32=a32-(l31*u12);
	l33=(a33-(l31*u13+l32*u23));
	printf("%f \t %f \t %f  \n",l11,l12,l13);
	printf("%f \t %f \t %f  \n",l21,l22,l23);
	printf("%f \t %f \t %f  \n",l31,l32,l33);
	printf("\n \n");
	printf("%f \t %f \t %f  \n",u11,u12,u13);
	printf("%f \t %f \t %f  \n",u21,u22,u23);
	printf("%f \t %f \t %f  \n",u31,u32,u33);
	return 0;
}