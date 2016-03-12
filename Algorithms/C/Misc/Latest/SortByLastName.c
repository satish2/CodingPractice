#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char *firstName;
	char *lastName;
} name;

void sort(name *, int st, int end);
void merge(name *names, int st, int mid, int end);
int compare(name name1, name name2);

int compare(name name1, name name2){

	return (strcmp(name1.lastName, name2.lastName));
}

void sort(name *names, int st, int end){
	
	if(st > end)
		return;
	int mid = (st+end)/2;
	sort(names,st,mid);
	sort(names,mid+1,end);
	merge(names,st,mid,end);
}

void merge(name *names, int st, int mid, int end){
	int i=0,j=0,k=0;
	int llen = (mid-st + 1);
	int rlen = (end-mid);
	name *left = (name *)malloc(sizeof(name)*llen);
	name *right = (name *)malloc(sizeof(name)*rlen);
	for(i=0;i<llen;i++)
		left[i] = names[st+i];
	for(j=0;j<rlen;j++)
		right[j] = names[mid+1+j];
	i=j=0;
	for(k=st;k<=end && i < llen && j < rlen;k++){
		int temp = compare(left[i],right[j]);
		if(temp > 0){ //left is greater
			names[k] = right[j];
			j++;
		} else {
			names[k] = left[i];
			i++;
		}	
	}
	while(i>llen && j < rlen && k<=end){
		names[k] = right[j];
		j++;
		k++;
	}
	while(j>rlen && i < llen && k<=end){
		names[k] = left[j];
		i++;
		k++;
	}
	free(left);
	free(right);
	return;
}	

int main(int argc, char *argv[]){
	
	int i=0,N = 10;
//
	name names[10] = {"\0"}; 
	for(i=0;i<N;i++){
		char *temp1, *temp2;
		scanf("%s", temp1);
		scanf("%s", temp2);
		strcpy(names[i].firstName,temp1);
		strcpy(names[i].lastName,temp2);
	}
	
	sort(names,0,9);
	for(i=0;i<N;i++){
		printf("LastName = %s FirstName=%s", (&names[i])->lastName,(&names[i])->firstName);
	}
}