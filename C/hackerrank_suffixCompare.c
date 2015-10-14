#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
/* Head ends here */
int check_sim(char *, char *);
long long int stringSimilarity(char a[]) {
	int i=0;
	for(i=0; i< 10; ++i){
		printf("%d \n", i);
	}
	return i;
}

int main() {
    int t, i;
    long long int res;
    scanf("%d",&t);
    char a[100001];
    for (i=0;i<t;i++) {
        scanf("%s",a);
        res=stringSimilarity(a);
        printf("%lld\n",res);  
    }

    return 0;
}
