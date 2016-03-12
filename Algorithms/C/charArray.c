#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _a {
	int x;
	int a[0];
	int p[0];
	int d;
}b;

int main(){
	
	int a1[0],a2[0],a3[0];
	printf("addr a1 = %d and size=%d\n",a1,sizeof(a1));
	printf("addr a2 = %d\n",a2);
	printf("addr a3 = %d\n",a3);
	a1[0] = 1;
	printf("value at a1 = %d\n",a1[0]);
	char *a = (char *)calloc(10,sizeof(char));
	strcpy(a,"hello");
	int len = strlen(a);
	int i= 0;
/*	for(;i<len;i++){
		char d = a[i+1];
		a[i+1] = a[i];
		a[i] = d;
		printf("%c swapped with %c \n",a[i],a[i+1]);
	}*/
	b *var = (b *)malloc(sizeof(b));
	int dx = malloc(0);
	int dy = 10;
	var->a[0] = 1;
	var->p[0] = 2;
	printf("struct addr = %d\n",var);
	printf("a addr = %d\n",var->a);
	printf("value at a %d\n",var->a[0]);
	printf("p addr = %d\n",var->p);
	printf("value at p %d\n",var->p[0]);
	printf("next addr = %d\n",&(var->d));
	printf("dx addr = %d\n",&dx);
	printf("dy addr = %d\n",&dy);
}

