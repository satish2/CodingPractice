#include <stdio.h>

int reversebits(int a){

	a = 2;
	//reverse bits in a
	int numOfBits = sizeof(a)*8;
	int i = 0;
	int j = numOfBits-1;
	while(i < j){
		int left = a >> j & 1;
		int right = a >> i & 1;
		if(left != right)
			a = a ^ (1 << i | 1 << j);

		i++;
		j--;
	}
	printf("reversed = %d\n",a);
	return a;
}

//http://stackoverflow.com/questions/5253194/implementing-logical-right-shift-in-c
int logical_right_shift(int x, int n)
{
    int size = sizeof(int) * 8; // usually sizeof(int) is 4 bytes (32 bits)
    return (x >> n) & ~(((0x1 << (size-1)) >> n) << 1);
}

int power(int a, int index){
	return a << index;
}

int getMask(int mask, int j){
	int i = 0;
	while(i < j){
		mask = mask << 1;
		mask = mask | 1;
		i++;
	}
	return mask;
}

void reversebytes(int a){
	
	printf("input a = %x\n",a);
	int numofbytes = sizeof(a);
	//4 --> (3,0) and (2,1) should be swapped
	int i = 0;
	int j = numofbytes-1;
	int orig_a = a;
	while(i < j){
		int mask = 0xFFFFFF00;
		int temp = numofbytes - j;
		int left = (a >> j*8) & 0xff;
		int right = (a >> i*8) & 0xff;
		a = a & getMask(mask,i*8);
		a = a & getMask(mask,j*8);
		a = a | (left << i*8 | right << j*8);
		i++;
		j--;
	}
	printf("reversed bytes = %x\n",a);
}


int main(int argc, char *argv[]){
	
	int rev = reversebits(2);
	reversebytes(0xF0F0F0FF);
}



