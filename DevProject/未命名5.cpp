#include "stdio.h"/*��ĳ����m��8�Ǻ�n��5�ǵ���Ʊ��ʹ����Щ��Ʊ����ϳ������ֲ�ͬ��ֵ������,m,n�Ӽ��������롣 */  
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
