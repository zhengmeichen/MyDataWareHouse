#include "stdio.h" /*若n的全部因子(包括1,不包括n本身)之和等于m，且m的全部因子(包括1,不包括m本身)之和等于n,  
且m不等于n，则将n和m称为亲密数。  
从键盘上输入k，输出k以内全部的亲密数。 提示：定义一个求数全部因子之和的函数。*/  
#include "math.h"  
#include "string.h" 
int f(int x) 
{
	int sum=0;
	for(int i=1;i<x;i++)
	{
		if(x%i==0)
		{
			sum+=i;
		}
	}
	return sum;
}
int main()  
{  
    int k,m,n,i;  
    int a[5000];
    for(i=0;i<5000;i++)
    {
    	a[i]=f(i);
	}
    scanf("%d",&k); 
	for(n=1;n<k;n++)  
    {
    	for(m=1;m<k;m++)
    	{
    		if(m!=n&&a[n]==m&&a[m]==n)
    		{
    			printf("%d,%d\n",n,m);
			}
		}
	}
    return 0;  
}  
