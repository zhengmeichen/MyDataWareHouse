#include "stdio.h" /*�Ӽ���������n���������ͼ�� */
#include "math.h"
int main() 
{ 
    int n,i,j; 
    scanf("%d",&n); 
    for(i=1;i<=n;i++)//������  
    { 
       for(j=1;j<=n-i;j++)//���ո� 
            printf(" "); 
       for(j=1;j<=i;j++) 
            printf("*");//���ǰ��� 
       for(j=i-1;j>=1;j--) 
            printf("*");//������� 
       printf("\n");    
    } 
    for(i=n-1;i>=1;i--)//������  
    { 
       for(j=1;j<=n-i;j++)//���ո� 
            printf(" "); 
       for(j=1;j<=i;j++) 
            printf("*");//���ǰ��� 
       for(j=i-1;j>=1;j--) 
            printf("*");//������� 
       printf("\n");  
    } 
	return 0;
}
