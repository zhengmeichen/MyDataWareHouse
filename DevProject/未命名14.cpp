#include "stdio.h"/*��֪���򼯺� A �� B �ֱ���� 10 ��Ԫ�أ�
 A �� B ��Ԫ�شӼ��������룬������� A-B ����Ԫ������ A ���������� B ��  */  
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

