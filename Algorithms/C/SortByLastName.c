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
	if(name1.lastName == NULL)
		return -1;
	else if(name2.lastName == NULL)
		return 1;
	return (strcmp(name1.lastName, name2.lastName));
}

void sort(name *names, int st, int end){
	
	if(st >= end)
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
	for(i=0;i<llen;i++){
		left[i].firstName = (char *)malloc(sizeof(char)*20);
		left[i].lastName = (char *)malloc(sizeof(char)*20);
		memset(left[i].firstName,'\0',20);
		memset(left[i].lastName,'\0',20);
		strcpy(left[i].firstName, names[st+i].firstName);
		strcpy(left[i].lastName, names[st+i].lastName);
	}
	for(j=0;j<rlen;j++){
		right[j].firstName = (char *)malloc(sizeof(char)*20);
		right[j].lastName = (char *)malloc(sizeof(char)*20);
		memset(right[j].firstName,'\0',20);
		memset(right[j].lastName,'\0',20);
		strcpy(right[j].firstName, names[mid+1+j].firstName);
		strcpy(right[j].lastName, names[mid+1+j].lastName);
	}

	i=j=0;
	for(k=st;k<=end && i < llen && j < rlen;k++){
		int temp = compare(left[i],right[j]);
		if(temp > 0){ //left is greater
		strcpy(names[k].firstName, right[j].firstName);
		strcpy(names[k].lastName, right[j].lastName);
			j++;
		} else {
		strcpy(names[k].firstName, left[i].firstName);
		strcpy(names[k].lastName, left[i].lastName);
			i++;
		}	
	}
	while(i>=llen && j < rlen && k<=end){
		strcpy(names[k].firstName, right[j].firstName);
		strcpy(names[k].lastName, right[j].lastName);
		j++;
		k++;
	}
	while(j>=rlen && i < llen && k<=end){
		strcpy(names[k].firstName, left[i].firstName);
		strcpy(names[k].lastName, left[i].lastName);
		i++;
		k++;
	}
	for(i=0;i<llen;i++){
		free(left[i].firstName);
		free(left[i].lastName);
	}
	for(j=0;j<rlen;j++){
		free(right[j].firstName);
		free(right[j].lastName);
	}
	free(left);
	free(right);
	return;
}	

int main(int argc, char *argv[]){
	
	int i=0,N = 10;
	FILE *fd = fopen("Names.txt","r");
	name *names = (name *)malloc(sizeof(name)*10); 
	for(i=0;i<N;i++){
		names[i].firstName = (char *)malloc(sizeof(char)*20);
		names[i].lastName = (char *)malloc(sizeof(char)*20);
		memset(names[i].firstName,'\0',20);
		memset(names[i].lastName,'\0',20);
		fscanf(fd, "%s", names[i].firstName);
		fscanf(fd, "%s", names[i].lastName);
	}
	sort(names,0,9);
	for(i=0;i<N;i++){
		printf("LastName = %s FirstName=%s\n", (&names[i])->lastName,(&names[i])->firstName);
	}
}
