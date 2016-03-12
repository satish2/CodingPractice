#include<stdio.h>
int main()
{
	 char a=0;
	 char b=0;
	 int i;
	 for(i=1;i>0;i++)
	 {
		 scanf("%c",&a);
		 if(a>b)
		 {printf("%c is greater \n",a);}
		 if(b>a)
{		 printf("%c is greater \n",b);}
		 if(a==b)
{		 printf("both are equal");}
		 b=a;
		 if(a=='0')
		 break;
	 }
return 0;
}	 	  