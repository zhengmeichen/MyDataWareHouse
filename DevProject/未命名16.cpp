#include "stdio.h"/*TomѧϰC��������������ʦJolie��JolieΪTom�����˵��Ե�ѧϰ�ƻ���
Ҫ��ÿ�����1��3����ϰ��Tom��1�������1����ϰ���ʵ���Tom�����n����ϰʱ���ж����ַ����� */  
#include "math.h" 
int tomPlan(int m);  
int tomPlan(int m)  
{  
    if(m==1) return 1;  
    else if(m==2) return 1;  
    else if(m==3) return 2;  
    else return tomPlan(m-1)+tomPlan(m-2)+tomPlan(m-3);  
}  
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
  
int  main()     
{     
   int m;     
   scanf("%d",&m);     
      
   printf("%d\n",tomPlan(m));     
  return 1;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
