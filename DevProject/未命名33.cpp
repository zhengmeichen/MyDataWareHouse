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
	};
	struct student stus[5];
	int i;
	for(i=0;i<5;i++)
	{
		scanf("%s %c %d %d %d %d %d",stus[i].name,&stus[i].sex,&stus[i].a,&stus[i].b,&stus[i].c,&stus[i].d,&stus[i].e);	
	}
	char c[20];
	scanf("%s",c);
	for(i=0;i<5;i++)
	{
		if(strcmp(stus[i].name,c)==0)
		{
			printf("%s %c %d %d %d %d %d\n",stus[i].name,stus[i].sex,stus[i].a,stus[i].b,stus[i].c,stus[i].d,stus[i].e);
			//break;
		}	
	}
	return 0;
}
