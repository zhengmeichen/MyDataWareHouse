#include "stdio.h" /*��4 �׷���ת��(�������Խ���Ϊ��,������Ԫ�ص��к���λ�û���)  */
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
	printf("���Ϊ��\n");
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
