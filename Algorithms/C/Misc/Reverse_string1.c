
#include<stdio.h>
#include<string.h>
void reverseString(char *);
void swap(char *,char *);
void main(){

reverseString("satish");

}
void reverseString(char *str){
    printf("%s\n",str);
    int i;
    char ch;
    int length = strlen(str);
    for(i=0;i<(strlen(str)/2);i++){
        int j= strlen(str)-i-1;
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
   }
printf("%s",str);
}

