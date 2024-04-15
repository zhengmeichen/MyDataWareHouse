
#include "stdio.h"
#include "math.h" 
#include "string.h"

int  main()
{
	int N;
	scanf("%d",&N);
	
	int a[N][N] = { 0 };
	printf("½á¹ûÎª£º\n");
	for (int k = 0; k < N; k++)
	{
		a[k][0] = 1;
	}
	for (int i = 1; i < N; i++)
		for (int j = 1; j <=i;j++)
		{
			a[i][j] = a[i - 1][j] + a[i-1][j - 1];
		}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf("%3d", a[i][j]);
		}
			
		printf("\n");
	}
	return 0;
}

