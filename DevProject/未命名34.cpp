#include "stdio.h"
#include "math.h"
#include "string.h"
int fan(int m,int n)
{
	int i,j;
	j=m*n;
	for(i=1;i<=j;i++)
	{
		if((i%m==0)&&(i%n==0))
		{
			return i;
		}
	}
}
int fun(int m,int n)
{
	int i;
	if(m>n)
	{
		for(i=n;i>=1;i--)
		{
			if(m%i==0&&n%i==0)
			{
				return i;
			}
		}	
	}
	else if(m<n)
	{
		for(i=m;i>=1;i--)
		{
			if(m%i==0&&n%i==0)
			{
				return i;
			}
		}
	}
}
int main()
{
	int m,n;
	scanf("%d %d",&m,&n);
	printf("%d %d\n",fun(m,n),fan(m,n));
	return 0; 
}

