#include "stdio.h"
#include "math.h"
#include "string.h"
int main()
{
	struct student
	{
		char name[20];
		char no[15];
		char national[20];
	};
	int i,j;
	struct student stus[3];
	for(i=0;i<3;i++)
	{
		scanf("%s",stus[i].name);
		scanf("%s",stus[i].no);
		scanf("%s",stus[i].national);
	}
	for(i=0;i<2;i++)
	{
		for(j=i+1;j<3;j++)
		{
			if(strcmp(stus[i].no,stus[j].no)>0)
			{
				struct student tmp;
				tmp=stus[i];
				stus[i]=stus[j];
				stus[j]=tmp;
			}
		}
	}
	for(i=0;i<3;i++)
	{
		printf("%s,%s,%s\n",stus[i].name,stus[i].no,stus[i].national);
	}
	return 0;
	
}
