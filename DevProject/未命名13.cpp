#include "stdio.h"/*编写名为 reversalNum的递归函数，函数原型为 void reversalNum(int n),
功能是输出翻转数。如参数为4321，输出为1234，假设n不超过5位数。*/
#include "math.h" 
void reversalNum(int m)
{
	int a,b;
	a=m;
	while(a!=0)
	{
		b=a%10;
		a=a/10;
		printf("%d",b); 
	}
	
	
}
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
  
int main()                        
{       
    int m;     
    scanf("%d",&m);     
    reversalNum(m);          
    printf("\n");   
return 1;    
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
