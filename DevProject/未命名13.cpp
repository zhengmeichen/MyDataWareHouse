#include "stdio.h"/*��д��Ϊ reversalNum�ĵݹ麯��������ԭ��Ϊ void reversalNum(int n),
�����������ת���������Ϊ4321�����Ϊ1234������n������5λ����*/
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
