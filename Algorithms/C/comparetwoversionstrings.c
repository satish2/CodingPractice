//Compare Two version strings

//"13.24.13.1" "14.24.0"
/*
 * First split based on . as delimiter
 * find the one with min length
 * Compare till that length
 * One with maximum value that happens first is the greater one
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define min(a,b) ((a) < (b) ? (a) : (b))
#define NEWLINE printf("\n"); 


char **split(char *string, int *len){
	int numberofdots = 0, i = 0, max_within_dots = 0, within_dots = 0;
	int length = strlen(string);
	while(i < length){
		if(string[i] == '.') {
			numberofdots++;
			if(within_dots > max_within_dots) max_within_dots = within_dots;
			within_dots = 0;
		} else {
			within_dots ++;
		}
		i++;
	}

	char **ret = (char **)malloc((numberofdots+1)*sizeof(char*));
	for(i = 0; i <= numberofdots; i++ ){
		ret[i] = (char *)calloc(max_within_dots,sizeof(char));
	}
	int retIndex = 0;
	int st = 0;

	while(st < length){
		i = 0;
		while(st < length && string[st] != '.'){
			ret[retIndex][i] = string[st];
			st++;
			i++;
		}		
		retIndex++;
		st++;
	}
	*len = numberofdots+1;
	return ret;
}

int whichIsMax(char **str1, char **str2, const int length){
	static int x = 0;
	int ret1 = strcmp(str1[x], str2[x]);
	if(ret1 == 0) {
		x++;
		if(x >= length) 
			return 0;
		else
			return whichIsMax(str1, str2, length);
	}
	return ret1;
}

int main(int argc, char *argv[]){
	
	if(argc < 3){
		printf("Incorrect input arguments. Execute as ./cvs <string1> <string2>");
		return;
	}
	int len1 = 0;
	int len2 = 0;
	char **str1_arr = split(argv[1], &len1);
	char **str2_arr = split(argv[2], &len2);
	printf("Length of 1 & 2 version string is %d and %d\n", len1, len2);
	int retVal = whichIsMax(str1_arr, str2_arr, min(len1, len2));
	if(retVal == 0)	{
		if(len1 > len2)
			printf("%s is greater than %s", argv[1], argv[2]);
		else if (len2 > len1)
			printf("%s is greater than %s", argv[2], argv[1]);	
		else
			printf("They are same");
	} else if(retVal > 0) 
		printf("%s is greater than %s", argv[1], argv[2]);
		else
		printf("%s is greater than %s", argv[2], argv[1]);
	NEWLINE
	return 0;
}
