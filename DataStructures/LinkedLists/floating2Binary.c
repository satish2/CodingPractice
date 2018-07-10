//floating to binary

#include <stdio.h>
#include <math.h>

#define DOUBLEPRECISION_BIAS 1023
#define DOUBLEPRECISION_EXPONENT_END_POS 11

#define FLOATING_BIAS 127
#define FLOATING_EXPONENT_END_POS 8

#define DOUBLE_END_POS 63
#define FLOAT_END_POS 31

void int2binary(char *a, int in, int strPos, int bits);
void fill_exp(char *a, int in, int strPos, int bits);

void int2binary(char *a, int in, int strPos, int bits){
	printf("input = %d\n",in);
	int pos = strPos + bits -1;
	while (in != 1 && pos > (strPos -1)){
		a[pos] = '0' + in%2;		
		in = in/2;
		pos--;
	}
}

void fill_exp(char *a, int in, int strPos, int bits){
	int pos = strPos + bits -1;
	printf("input = %d, bits = %d, pos=%d\n",in, bits, pos);
	while (in != 0 && pos > (strPos -1)){
		a[pos] = '0' + in%2;		
		in = in/2;
		pos--;
	}
}

int main(int argc, char *argv[]){
	
	double in = 0.0;
	int pos = 0;
	char a[65] = {'0'};
	int bias, end_pos,last_bit;
	a[64]='\0';
	printf("Input Decimal ? ");
	scanf("%lf",&in);
	a[pos] = '0';
	if(in < 0){
		a[pos] = '1';
		in = in*-1;
	}

	if(*argv[1] == 'd'){
		bias = DOUBLEPRECISION_BIAS;
		end_pos = DOUBLEPRECISION_EXPONENT_END_POS;
		last_bit = DOUBLE_END_POS;
	} else {
		bias = FLOATING_BIAS;
		end_pos = FLOATING_EXPONENT_END_POS;	
		last_bit = FLOAT_END_POS;
	}

	int integer_part = (int)in;
	int bits = (int)(log((double)integer_part)/(log((double)2)));
	int bits_bits = (int)(log((double)(bits+bias))/(log((double)2)));
	if(integer_part != 0) {
		int2binary(a,integer_part,end_pos+1,bits);
	}

	fill_exp(a,bits+bias,1,bits_bits+1);
	pos = end_pos + 1 + bits;
	in = in - (integer_part);
	while (pos <=last_bit){
		in = in *2;
		if(in >= 1){
			in = in-1;
			a[pos]	= '1';
		} 
		else 
			a[pos] = '0';
		pos++;
	}
	printf("normalized mantissa = %s\n", a);
}
