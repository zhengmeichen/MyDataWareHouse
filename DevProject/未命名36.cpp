#include "stdio.h"
#include "math.h"
#include "string.h"
int main() 
{
	struct student
	{
		char name[20];
		char sex;
		int a;
		int b;
		int c;
		int d;
		int e;
		float avg; 
	};
	struct student stus[5];
	int i;
	for(i=0;i<5;i++)
	{
		scanf("%s %c %d %d %d %d %d",stus[i].name,&stus[i].sex,&stus[i].a,&stus[i].b,&stus[i].c,&stus[i].d,&stus[i].e);	
	}
	for(i=0;i<5;i++)
	{
		stus[i].avg=(stus[i].b+stus[i].c+stus[i].d+stus[i].e)/4.00;
		{
			printf("%s %c %d %f\n",stus[i].name,stus[i].sex,stus[i].a,stus[i].avg);
			//break;
		}	
	}
	return 0;
}
