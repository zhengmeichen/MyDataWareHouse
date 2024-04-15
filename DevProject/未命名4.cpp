#include "stdio.h"
#include "math.h" 
int main()
{
	int A[11]={1,11,21,31,41,51,61,71,81,91};
	int n,i,j;
	scanf("%d",&n);
	for(i=0;i<10;i++)
	{
	    if(A[i]>n)  
        {  
            break;  
        }  
    }  
    for(j=9;j>=i;j--)  
    {  
        A[j+1]=A[j];  
    }  
    A[i]=n;  
    for(i=10;i>=0;i--)  
    {  
        printf("%d,",A[i]);  
    }  
    printf("\n");  
    return 0;  
} 



