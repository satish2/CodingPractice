/*    Quick Merge sort 
 *    2008A7PS061G
 *    26/08/2010
 */


#include<stdio.h>

void merge_sort(int *a,int i,int j);    /* FUNCTION DECALARAION */
int  quick_merge(int *a,int p,int r);
int partition(int *a,int p,int r);
 
int main()
{
  int num,i;
  scanf("%d",&num);
  int a[num];
   for(i=0;i<num;i++)
     {
      scanf("%d",&a[i]);
     }
   merge_sort(a,0,num-1);
    for(i=0;i<num;i++)
     {
       printf(" %d ", a[i]);
     }
   return 0;
}
                     
void merge_sort(int *a,int i,int j)
{
 
  if((j-i)>1)
  {
    merge_sort(a,i,(i+j)/2);
    merge_sort(a,((i+j)/2)+1,j);
    quick_merge(a,i,j);
  }

}


int quick_merge(int *a,int p,int r)
{


   int q;
   if(p<r)
   { 
     q= partition(a,p,r);
     quick_merge(a,p,q-1);
     quick_merge(a,q+1,r);
   }
}



int partition(int *a,int p,int r)                      /* PARTITION FUNCTION */
{
   int m;
    
   int x=a[p]; 
   
   int i=p,j,temp;
   m=((p+(r-p)/3));/* PIVOT IS AN ELEMENT IN THE MID OF FIRST SUBARRAY */
   x=a[m];
   temp=a[m];
   a[m]=a[p];
   a[p]=temp;
   
   for(j=p+1;j<=r;j++) 
     {
       if(a[j]<=x)
       { 
         i=i+1;
         temp=a[i];
         a[i]=a[j];
         a[j]=temp;
       }
    }
  temp=a[i];
  a[i]=x;
  a[p]=temp;
  return i;
} 




/*
 * COMPLEXITY OF QUICK MERGE SORT::
 * WORST CASE  = N^2
 * BEST CASE   = N*((log n)^2)
 * AVERERAGE   = (N^2)*(log(n)) 
 */	 
