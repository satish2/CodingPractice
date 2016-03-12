
#include<stdio.h>
#include<string.h>

void reverseString();

void main(){
reverseString();
}

void reverseString(){
    char *str;
    printf("enter string\n");
    scanf("%s",str);
    printf("%s\n",str);
    int i,j;
    int length = strlen(str);
    for(i=0;i<(length/2);i++){
        char ch;
        j= length-i-1;
        ch = str[j];
        str[j] = str[i];
        str[i] = ch;
   }
printf("%s",str);
}

