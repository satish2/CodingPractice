#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

//Sudoku validator
//First have all the entries of sudoku in 9*9 matrix. 

int sudoku[9][9]={0};

int checkingrid(int base,int base2){
	int i,j;
	for(i=base;i<3+base;i++){
		int sum = 0;	
		for(j=base2;j<3+base2;j++){
			if(sudoku[i][j] < 1 || sudoku[i][j] > 9)
				return -1;
			sum += sudoku[i][j];
		}
		if(sum != 45){
		return -1;
		}
	}
	return 0;
}



int main(void){
	
   //  printf("populated values\n");
	

	int i=0,j=0;
    char number[9];
	for(i=0;i<9;i++){
		scanf("%s",number);
        for (j=0;j<9;j++){
            sudoku[i][j] = number[j] - '0';
        }
	}
   // printf("populated values\n");

	//Now take values at index 0,3,6 in each row
	//DO SUM in each row and column
	for(i=0;i<9;i++){
		int sum = 0;	
		for(j=0;j<9;j++){
			sum += sudoku[i][j];
		}
		if(sum != 45){
		printf("Incorrect");
		return -1;
		}
       
	}
   // printf("Compared all rows \n");
	for(j=0;j<9;j++){
		int sum = 0;	
		for(i=0;i<9;i++){
			sum += sudoku[i][j];
		}
		if(sum != 45){
		printf("Incorrect");
		return -1;
		}
	}
    //printf("Compared all columns \n");

	i=0,j=0;
	int ret=0;
	while(ret != -1){
		ret = checkingrid(i,j);
        if(j==6){
            if(i==6)
                return 0;
            i = i+3;
            j=0;
        }
        j = j+3;
	}
	if(ret == -1){
		printf("Incorrect");
		return 0;
	}
	printf("Correct");
	return 0;
}



