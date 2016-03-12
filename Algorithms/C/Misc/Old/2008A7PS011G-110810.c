//errors in line 14 and 76
#include<stdio.h>
void mergesort(int a[],int,int);
void merge(int a[],int,int,int);
void insertsort(int a[],int,int);
volatile int size;
int main()
{
	int i;
 	int low=0;					
        int high ;
	scanf("%d",&size);					//size is size of given array
	int a[size];
        high=size-1;						/*error*/
	for(i=0;i<size;i++)
	{
 		scanf("%d",&a[i]);				//inputting numbers into our array
 	}
	mergesort(a,low,high);					//calling mergesort to sort array
for(i=0;i<size;i++)
{
  printf("%d \t",a[i]);
}
return 0;
}
void mergesort(int b[],int c,int d)
{
 int mid;							//mid is middle element of array of size d and c is position 
 mid=(c+d)/2;							//of lowest element of array	
 if(c+10<=d)
 {
  mergesort(b,c,mid);
  mergesort(b,mid+1,d);
  merge(b,c,mid,d);
 }
 else							//if size of array is less than 10 then it calls for insertion sort
 { 	
  insertsort(b,c,d);
 }
}	
void merge(int e[],int low,int mid,int high)
{
 int i;
 int p=low;
 int r=low;
 int q=mid+1;
 int f[size];
 while((p<=mid)&&(q<=high))
 { 
    if(e[p]<e[q])					//f is merged array 	
    {
        f[r]=e[p];
      	r++;
       	p++;
    }
    else
    {
    	f[r]=e[q];
   	r++;	
   	q++;
    }	
 }	
while(p<=mid)						//is any of subarrays' elements are left out they are added in end of  
{							//merged array 
 f[r]=e[p];
 r++;
 p++;
}
while(q<=high)
{
 f[r]=e[q];
 r++;
 q++;
}
for(i=0;i<r;i++)					//finally merged array is copied into original array 
{ 
 e[i]=f[i];
}
}

void insertsort(int ar[],int low,int high)
{
int i,j,l;
int temp=0;

 for(j=low+1;j<=high;j++)
 {	
	for(i=low;i<j;i++)
 	{
 		if(ar[i]>ar[j])
		{
		 temp=ar[j];
		 l=j;
		 while(l!=i)
		  {
		     ar[l]=ar[l-1];
    		     l--;
        }
		ar[i]=temp;
		}
   }
 }	
}

