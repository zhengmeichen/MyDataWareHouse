#include "stdio.h"/*������һ�������飬��������ĳ���±�ֵ���Ԫ��ֵС��ĳ���±�ֵ����С��Ԫ��ֵ��������һ������
��������a�У� ����i < j �� a[i] > a[j]���������һ������
Ҫ������ΪreverseOrder�ĺ���������ԭ��Ϊint reverseOrder(int b[],int )��
���������Ǽ�������������з���ĸ���������˵�д��¹��������⡣��*/  
#include "math.h" 
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */

#include <stdio.h>      
int main()   
{   
    int a[10],i;   
    int n;   
    int reverseOrder(int a[],int );   
    scanf("%d",&n);   
    for(i=0;i<n;i++)   
       scanf("%d",&a[i]);   
    printf("%d\n",reverseOrder(a,n));  

return 1; 
}

/* PRESET CODE END - NEVER TOUCH CODE ABOVE */
int reverseOrder(int b[],int )
{
	int c[10];
	int x,y,count=0;
	for(x=0;x<10;x++)
	{
		for(y=x+1;y<10;y++)
		{
			if(c[x]>c[y])
			{
				count++;
			}
		}
	}
	return count;
}
