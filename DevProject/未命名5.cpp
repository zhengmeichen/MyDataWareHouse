#include "stdio.h"/*从某人有m张8角和n张5角的邮票，使用这些邮票能组合出多少种不同面值的邮资,m,n从键盘上输入。 */  
#include "math.h"  
int main()  
{  
    int m,n,a,b,c,x=1,y=0,count=0,max;
    scanf("%d%d",&m,&n);
    max=8*m+n*5;
    for(c=0;c<=max;c++)
    {
    	for(a=0;a<=m;a++)
    	{
    		for(b=0;b<=n;b++)
    		{
    			if(c==8*a+5*b)
    			{
    				y=x;
					x=c;
					count++;
				if(y==x)
				{
					count=count-1;
				}
			    }
			}
		}
	}
	printf("%d\n",count);
	return 0;  
}  
