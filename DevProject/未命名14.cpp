#include "stdio.h"/*已知有序集合 A 、 B 分别包含 10 个元素，
 A ， B 的元素从键盘上输入，输出补集 A-B （其元素属于 A ，但不属于 B ）  */  
#include "math.h" 
int f(int a,int B[10])
{
	for(int i=0;i<10;i++)
	{
		if(B[i]==a)
		{
			return 1;
		}	
	}
	return 0;
}
int main()
{
	int A[10],B[10];
	for(int i=0;i<10;i++)
	{
		scanf("%d",&A[i]);
	}
	for(int j=0;j<10;j++)
	{
		scanf("%d",&B[j]);
	}
	for(int i=0;i<10;i++)
	{
		int rtn=f(A[i],B);
		if(rtn==0)
		{
			printf("%d,",A[i]);
		}
	}
	printf("\n");
	return 0;
} 

