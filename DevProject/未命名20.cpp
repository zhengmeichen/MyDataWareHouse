#include "stdio.h"  /*�Ӽ���������һ���ַ������ڵ�һ���ո񴦽��ַ����ָ�Ϊ2���Ӵ���Ҫ������ΪseparationString�ĺ�����
����ԭ��Ϊ char *separationString(char *myString)��û�пո�ʱ����NULL�� */
#include "math.h" 
#include "string.h" 
char *separationString(char *p)
{
	for(int i=0;i<20;i++,p++)
	{
		if(*p==0)
		{
			break;
		}
		if(*p==' ')
		{
			*p=0;
			break;
		}
	}
	p=p+1;
	return p;
}	
/* PRESET CODE BEGIN - NEVER TOUCH CODE BELOW */  
  
int main()     
{     
   char str[20];     
   char *p;     
   gets(str);     
   p=separationString(str);     
   puts(str);     
   puts(p);     
}  
  
/* PRESET CODE END - NEVER TOUCH CODE ABOVE */  
