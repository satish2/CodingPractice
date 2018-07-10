#include <stdlib.h>
#include <string.h>
void mergesort(char *str, int start, int end);
void merge(char *str, int st, int mid, int end);

void mergesort(char *str, int start, int end){
	int len = 1 + end - start;
	if(len < 2 || start > end)
		return;
	int mid = (start + end + 1)/2;
	mergesort(str, start, mid-1);
	mergesort(str,mid, end);
	merge(str,start,mid,end);
}

void merge(char *str, int st, int mid, int end){
	
	int llen = mid - st;
	int rlen = end - mid + 1;	
	char *left = (char *)calloc(llen+1,sizeof(char));
	char *right = (char *)calloc(rlen +1, sizeof(char));
	strncpy(left,str+st,llen);
	strncpy(right,str+mid,rlen);
	int k=0,i=0,j=0;
	for(k=0;k<=(end-st);k++){
		if(right[j] == '\0' && left[i] == '\0'){
			break;
		} else if (left[i] == '\0'){
			str[k+st] = right[j];
			j++;
		} else if (right[j] == '\0'){
			str[k+st] = left[i];
			i++;
		} else if (left[i] <= right[j]){
			str[k+st] = left[i];
			i++;
		} else if (right[j] < left[i]){
			str[k+st] = right[j];
			j++;
		}
	}
	free(left);
	free(right);
}
