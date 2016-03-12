#include <stdio.h>

int comparisons = 0, assignments = 0;

void Merge(int *A, int l, int m, int n)
    {
    int i, j, k, B[n-l+1];
    i = l;
    j = m+1;
    k = 0;
    while(i <= m && j <= n)
        {
        if(A[i] < A[j])
            {
            B[k] = A[i];
            i++;
            }
        else
            {
            B[k] = A[j];
            j++;
            }
        comparisons++;
        assignments++;
        k++;
        }
    while(i <= m)
        {
        B[k] = A[i];
        i++;
        k++;
        assignments++;
        }
    while(j <= n)
        {
        B[k] = A[j];
        j++;
        k++;
        assignments++;
        }
    for(k = 0; k < n-l+1; k++)
        {
        A[k+l] = B[k];
        assignments++;
        }
    }

void MergeSortSplitAtInversions(int *A, int m, int n)
    {
    int breakpoint = m;
    while(breakpoint < n && A[breakpoint] <= A[breakpoint+1])
        {
        breakpoint++;
        comparisons++;
        }
    if(breakpoint < n)
        {
        MergeSortSplitAtInversions(A,m,breakpoint);
        MergeSortSplitAtInversions(A,breakpoint+1,n);
        Merge(A,m,breakpoint,n);
        }
    }

int main(void)
    {
    int n;
    scanf("%d",&n);
    int A[n];
    int i;
    for(i = 0; i < n; i++) scanf("%d",A+i);
    MergeSortSplitAtInversions(A,0,n-1);
    for(i = 0; i < n; i++) printf("%d\t",A[i]);
    printf("\n%d\n%d\n",comparisons,assignments);
    return 0;
    }

