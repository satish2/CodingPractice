/*.
Given a string "Hellol, Count the number of substrings that are palindromes
Example : 
1. each character (6) + "lol" + "ll"
2. abcdefgf -> each character + "fgf"
*/


#include <stdio.h>
#include <string.h>

int find_nop(char *str, int st, int end);

char *substring(char *str, int st, int end){

	int len = end-st+1;
	char *ans = (char *)calloc(len,sizeof(char));
	int i = 0;
	for(;i<=len;i++)
		ans[i] = str[st+i];
		
	return ans;
}

int main(void) {
	// your code goes here
	char *str = (char *)calloc(100,sizeof(char));
	//strcpy(str,"dskjkd");
	scanf("%s", str);
	int len = strlen(str);
	find_nop(str,0,len-1);
	free(str);
	return 0;
}

int find_nop(char *str, int st, int end){

 int max_length = end-st + 1;
 int len = 1;
 int i = 0;
 int j= 0;
 
 int mat[100][100];
 for(i=0;i<max_length;i++){
 	mat[i][i] = 1;
 	for(j=0;j<len;j++){
 		if(i != j)
 			mat[i][j] = 0;
 	}
 }
 for(len = 2; len < max_length; len++){
 	for(i=max_length-len-1;i>=0;i--){
 		for(j = i+len-1; (j-i) <= len && j<max_length;j++){
 			//printf("i=%d,j=%d\n",i,j);
 			if(str[i] == str[j]){
 				if(i <= j-2 && mat[i+1][j-1] == 1 ){
 					mat[i][j] = 1;
 				} else if (i+1 == j){
 					mat[i][j] = 1;
 				}
 			} else {
 				mat[i][j] = 0;
 			}
 		}
 	}
 }
 int count = 0;
  for(i=0;i<len;i++){
 	for(j=0;j<len;j++){
 			count += mat[i][j];
 	}
 }
 
 printf("%d",count);
 }
