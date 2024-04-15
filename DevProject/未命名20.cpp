#include "stdio.h"  /*从键盘上输入一个字符串，在第一个空格处将字符串分割为2个子串。要求定义名为separationString的函数，
函数原型为 char *separationString(char *myString)，没有空格时返回NULL。 */
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
