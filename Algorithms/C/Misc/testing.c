#include<stdio.h>
#include<string.h>

void main(){

char *String = "satish";
int len = strlen(String);
char temp;
printf("%d\n",len);
int i = 0;
for(i=0;i<len/2;i++){
    temp = String+i;
    String[i] = String+len-i-1;
    String[len-i-1] = temp;
}
printf("%s",String);
}
