#include "stdio.h"/*������ΪtheDay�ĺ���������ԭ����int theDay(int year,int month,int day)��
�����Ƿ��ظ�������һ���еĵڼ��졣
������ΪleapYear�ĺ����������ж��Ƿ������꣬����ԭ��Ϊint leapYear(int year),���������꺯������1�����򷵻�0��*/  
#include "math.h"
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
 
#include "stdio.h"   
int main()     
{     
    int theDay(int,int,int);     
    int y,m,d;     
    scanf("%d%d%d",&y,&m,&d);     
    printf("%d\n",theDay(y,m,d));     
    
  return 1;  
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
int a,b,y,m,d;
int leapYear(int y);
int leapYear(int y)
{
	if(y%4==0&&y%100!=0||y%400==0)
	return 1;
	else
	return 0;
}
int theDay(int y,int m,int d);
int theDay(int y,int m,int d)
{
	int x[12]={0,31,59,90,120,151,181,212,243,273,304,334};
	int a,b;  
	a=x[m-1]+d;
	b=x[m-1]+d+1;
	if(leapYear(y)==0)
	{
		return a;
	}
	else 
	{		
		return b;
	}
}
