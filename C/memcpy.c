#include <stdio.h>
#include <stdlib.h>

void my_memcpy(int *dest, int *src, int size){
	char *d = (char *)dest;
	char *s = (char *)src;
	int loops = size/sizeof(int);
	int i = 0;
	for(i=0;i<loops;i++){
		*(int *)d = *(int *)s;
		d = d + sizeof(int);
		s = s + sizeof(int);
	}
	loops = size % sizeof(int);
	for(i=0;i<loops;i++){
		*d = *s;
		d++;
		s++;
	}
}



int main(int argc, char *argv[]){
		
	int *dest = (int *)malloc(sizeof(int)*10);
	int *src = (int *)malloc(sizeof(int)*11);
	int size = 10;
	int i=0;
	for(i=0;i<11;i++){
		src[i] = i;
	}
	my_memcpy(dest,src,size*4); //multiplied by 4 because size mentions how many bytes should be copied
	for(i=0;i<10;i++){
		printf("%d\t",dest[i]);
	}
	printf("\n");
	free(dest);
	free(src);
}
