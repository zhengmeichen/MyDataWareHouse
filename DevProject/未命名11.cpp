#include "stdio.h"/*从键盘上输入一个正数n，输出所有和为n 连续正数序列。（传说中的网易面试题） */  
#include "math.h"   
int main()
{
	int n,i,sum=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		sum=0;
		int a=i;
		for(int j=a;j<n;j++)
		{
			sum+=j;
			if(sum==n)
			{
				for(int b=a;b<j;b++)
				{
					printf("%d+",b);
				}
				printf("%d\n",j);
			}
		}
	}
    return 0;
}

