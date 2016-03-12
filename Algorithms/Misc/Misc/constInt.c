#include<stdio.h>
void main(){
int a = 1;
const int d = a; // here also d 's value cannot be changed
const int *e; // here *e cannot be changed, but e can be changed
const (int *) f = a;
e = &a;
e = 5;
//const (int *) f = 7;

printf("d = %d, e = %d", d,e);


}
