#include "stdio.h" /*��n��ȫ������(����1,������n����)֮�͵���m����m��ȫ������(����1,������m����)֮�͵���n,  
��m������n����n��m��Ϊ��������  
�Ӽ���������k�����k����ȫ������������ ��ʾ������һ������ȫ������֮�͵ĺ�����*/  
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
