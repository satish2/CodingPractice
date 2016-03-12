//BigInteger Addition
#include <stdlib.h>
#include <stdio.h>

typedef struct BigInt {
	unsigned char *arr;
	char extra;
	int length;
}bigint;

void readBigInt(bigint *num){
	char *arr = num->arr;
	int MAXSIZE = 100;
	int i= 0;
	unsigned char temp = '\0';
	int ret = -1;
	while(1){
		if(i >= MAXSIZE-1){
			arr = realloc(arr, i*2);
			MAXSIZE = i*2;
		}

		ret = scanf("%c",&temp);
		if( ret == EOF || temp == '\n' || temp == ' '){
			break;			
		}
		else {
			temp = temp << 4;
			arr[i] = 0x00 | temp;
		}
		ret = scanf("%c",&temp);
		if( ret ==EOF || temp == '\n' || temp == ' '){
			num->extra = 1;				
			i++;				
			break;
		} else {
			temp = temp & 0x0F;
			arr[i] = arr[i] | temp;
		}
		i++;
	}
	arr[i] = '\0';
	num->length = i;
}

void printBigInt(bigint *num){
	char *arr = num->arr;
	int len = num->length;
	char extra = num->extra;
	int j = 0;
	char temp;
	for(j = 0; j<len;j++){
		temp = arr[j];
		temp = temp >> 4;
		temp = temp & 0x0F;
		printf("%d",temp);
		if(j == len-1 && extra == 1){
			break;	
		}
		temp = arr[j];
		temp = temp & 0x0F;
		printf("%d",temp);
	}
	printf("\n");	
}

int main(int argc, char *argv[]){
	
	bigint *num1 = (bigint *)malloc(sizeof(bigint));
	bigint *num2 = (bigint *)malloc(sizeof(bigint));
	num1->arr = (unsigned char *)calloc(100,sizeof(unsigned char));
	num2->arr = (unsigned char *)calloc(100,sizeof(unsigned char));
	readBigInt(num1);
	readBigInt(num2);
	printBigInt(num1);
	printBigInt(num2);
	return 0;
}
