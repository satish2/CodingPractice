#include <stdio.h>

typedef struct satish {

 char s; //1
 int i; //4
 double d; //8
 void *p; //4
 int a[0]; //4
 int *b;
}s;

int main(void) {
	// your code goes here
	printf("%d\n",sizeof(struct satish));
	s *test = (s *)malloc(sizeof(s));
	printf("%d\n", &(test->s));
	printf("%d\n", &(test->i));
	printf("%d\n", &(test->d));
	printf("%d\n", &(test->p));
	printf("%d\n", &(test->a[0]));
	printf("%d\n", &(test->b));
	return 0;
}

