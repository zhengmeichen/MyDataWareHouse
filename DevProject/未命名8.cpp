#include "stdio.h" /*�� s �� a+aa+aaa+aaaa+���� ��ǰ n ��ͣ�
 a �� n �Ӽ��������룬������ 5 �� 3 ������ 5 �� 55+555 ��ֵ��  */
#include "math.h"
int main()
{
	int a,sum=0,n;
	scanf("%d%d",&a,&n);
	int b=a;
	for(int i=1;i<=n;i++)
	{
		sum+=b;
		b=b*10+a;
	}
	printf("%d\n",sum);
	return 0;
}
