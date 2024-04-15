#include "stdio.h"/*定给定一整型数组，若数组中某个下标值大的元素值小于某个下标值比它小的元素值，称这是一个反序。
即：数组a中， 对于i < j 且 a[i] > a[j]，则称这是一个反序。
要求定义名为reverseOrder的函数，函数原型为int reverseOrder(int b[],int )，
函数功能是计算出数组中所有反序的个数。（传说中创新工厂笔试题。）*/  
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
