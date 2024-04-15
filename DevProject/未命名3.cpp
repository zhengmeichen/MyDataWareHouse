#include "stdio.h"/*定义递归函数conversion，将10进制数转换为n进制数，n为2－16之间的数，函数原型为void conversion(int m,int n)，其中m为要转换的数，n为进制。
16进制中，10 用A表示，11用B表示，依次类推。 */  
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
