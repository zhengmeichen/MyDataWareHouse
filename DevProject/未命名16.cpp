#include "stdio.h"/*Tom学习C，遇到了温柔老师Jolie，Jolie为Tom做出了弹性的学习计划，
要求每天完成1至3个练习，Tom第1天完成了1个练习，问到当Tom完成了n个练习时，有多少种方法。 */  
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
