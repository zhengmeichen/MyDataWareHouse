#include "stdio.h"/*����ݹ麯��conversion����10������ת��Ϊn��������nΪ2��16֮�����������ԭ��Ϊvoid conversion(int m,int n)������mΪҪת��������nΪ���ơ�
16�����У�10 ��A��ʾ��11��B��ʾ���������ơ� */  
#include "math.h"
void conversion(int m,int n); 
void conversion(int m,int n) 
{ 
  int i,a[15],t=0; 
   while(m!=0) 
    { 
        i=m%n; 
        m=m/n; 
        a[t]=i; 
        t++; 
       //printf("%d,%d\n",i,t); 
    } 
  for(i=0;i<t;i++) 
    { 
        if(a[t-1-i]<10) 
	    {
	  		printf("%d",a[t-1-i]);
	    } 
	    else printf("%c",'D'); 
    } 
}  
 
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
  
int main()     
{     
   int num;     
   int n;     
   scanf("%d%d",&num,&n);     
   conversion(num,n);     
   printf("\n");     
return 1;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
