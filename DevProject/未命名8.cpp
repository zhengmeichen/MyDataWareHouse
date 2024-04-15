#include "stdio.h" /*求 s ＝ a+aa+aaa+aaaa+…… 的前 n 项和，
 a 和 n 从键盘上输入，如输入 5 和 3 ，则求 5 ＋ 55+555 的值。  */
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
