//String rotate
#include<stdio.h>
#include<string.h>

void main(){
char *String;
int i;
printf("enter String :  ");
String = (char *)malloc(sizeof(char)*10);
gets(String);
//first of all i need to find length of string;
int stringlength = strlen(String);
char temp = String[stringlength-1];
int count = 2;
while(count !=0){
for( i = stringlength-1; i>0;i--){
        String[i]=String[i-1];
}
count--;
}
String[1]= temp;
printf("%s",String);
}
