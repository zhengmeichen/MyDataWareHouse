#include "stdio.h"
#include "math.h"
#include "string.h"
int main() 
{
	int count=0;
	struct student
	{
		char name[20];
		char sex;
		int a;
		int b;
		int c;
		int d;
		int e;
	};
	struct student stus[5];
	int i;
	for(i=0;i<5;i++)
	{
		scanf("%s %c %d %d %d %d %d",stus[i].name,&stus[i].sex,&stus[i].a,&stus[i].b,&stus[i].c,&stus[i].d,&stus[i].e);	
	}
	for(i=0;i<5;i++)
	{
		if(stus[i].b<60||stus[i].c<60||stus[i].d<60||stus[i].e<60)
		{
			count++;
			if(count>=2)
			{
				printf("%s\n",stus[i].name);
			}
		} 
			
	}
	return 0;
}
