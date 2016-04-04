#include <stdio.h>

int main(void) {
	// your code goes here
	int x = 0xabcd3222;
	int y = 0x0;
	int count = (sizeof(int)*8);
	int i = 0;
	int temp = 0x0F;
	while(i < count){
		y = y << 4;
		y = y | (x & temp);
		x = x >> 4;
		i = i + 4;
	}
	printf("%x\n",y);
	return 0;
}

