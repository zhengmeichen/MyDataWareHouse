#include "stdio.h"/*从从键盘上输入n，输出完全数2－n间的所有完全数。 
一个数其所有的真因子（即除了自身以外的约数）的和（即因子函数），恰好等于它本身。如果一个数恰好等于它的因子之和，
则称该数为“完全数”。第一个完全数是6，第二个完全数是28，第三个完全数是496。 */ 
#include "math.h"
int main()
{
	int n,i,a,sum;
	scanf("%d",&n);
	for(i=2;i<=n;i++)
	{
	    sum=0;
		for(a=1;a<i;a++)
		{
			if(i%a==0)
			{
				sum+=a;
			}
		}
		if(sum==i)
		{
			printf("%d\n",i);
		}	
	} 
	return 0;
}
