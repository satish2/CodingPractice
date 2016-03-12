#include <stdio.h>

int comparisons = 0, assignments = 0;

void InsertionSort(int *A, int n)
    {
    int i, j = 1;
    for(i = 1; i < n; i++)
        {
        int k = 0;
        while(k < i && A[k] <= A[j])
            {
            k++;
            comparisons++;
            }
        int temp = A[j];
        assignments++;
        int l;
        for(l = j; l > k; l--)
            {
            A[l] = A[l-1];
            assignments++;
            }
        A[k] = temp;
        assignments++;
        comparisons++;
        j++;
        }
    }

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

void MergeSortWithInsertion(int *A, int m, int n)
    {
    if(m < n-9)
        {
        MergeSortWithInsertion(A,m,(m+n)/2);
        MergeSortWithInsertion(A,(m+n)/2+1,n);
        Merge(A,m,(m+n)/2,n);
        }
    else InsertionSort(A+m,n-m+1);
    }

int main(void)
    {
    int n;
    scanf("%d",&n);
    int A[n];
    int i;
    for(i = 0; i < n; i++) scanf("%d",A+i);
    MergeSortWithInsertion(A,0,n-1);
    for(i = 0; i < n; i++) printf("%d\t",A[i]);
    printf("\n%d\n%d\n",comparisons,assignments);
    return 0;
    }

