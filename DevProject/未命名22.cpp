#include "stdio.h" /*将4 阶方阵转置(即按主对角线为轴,将矩阵元素的行和列位置互换)  */
#include "math.h" 
#include "string.h"
#define m 4
#define n 4
int main()
{
	int a[m][n],count=0;
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[i][j]);
		}
	}
	printf("结果为：\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			printf("%d ",a[j][i]);
			count++;
			if(count%4==0)
			{
				printf("\n");
			}
		}
	}
	return 0;
} 
