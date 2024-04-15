#include "stdio.h"/*从键盘上输入10个国名，输出其中国名长度大于平均数的国名。  */  
#include "math.h" 
#include "string.h" 
int main() 
{
	int i;
	float sum=0;
	char a[10][50];
	for(i=0;i<10;i++)
	{
		gets(a[i]);
	}
	for(i=0;i<10;i++)
	{
		sum+=strlen(a[i]);
	}
	double avg=sum/10.00;
	printf("结果为：\n");
	for(i=0;i<10;i++)
	{
		
		if(strlen(a[i])>avg)
		{
			puts(a[i]);
		}
	}
	return 0;
}
