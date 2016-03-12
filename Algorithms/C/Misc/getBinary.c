#include <stdio.h>

int main(){
	int c,k,n=32;
	
	for (c = 31; c >= 0; c--)
  {
    k = n >> c;
	printf("VALUE OF K IS %d and C = %d and bitwiseAND is %d\n", k,c,k & 1);
/*    if (k & 1)
     // printf("1");
    else
      //printf("0");*/
  }
	  printf("\n");
 
  return 0;
}