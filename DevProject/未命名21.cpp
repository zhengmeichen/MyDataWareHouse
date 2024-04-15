#include "stdio.h"
#include "math.h"
#include "string.h" 
int main()
{
	int n;
	scanf("%d",&n);
	switch(n)
	{
		case 1: printf("yes\n");break;
		case 2: printf("no\n");break;
		default :printf("nutual\n");break;
	}
	return 0;
}
