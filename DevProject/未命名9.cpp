#include "stdio.h" /*从键盘上输入n，输出菱形图形 */
#include "math.h"
int main() 
{ 
    int n,i,j; 
    scanf("%d",&n); 
    for(i=1;i<=n;i++)//上三角  
    { 
       for(j=1;j<=n-i;j++)//画空格 
            printf(" "); 
       for(j=1;j<=i;j++) 
            printf("*");//输出前半边 
       for(j=i-1;j>=1;j--) 
            printf("*");//输出后半边 
       printf("\n");    
    } 
    for(i=n-1;i>=1;i--)//下三角  
    { 
       for(j=1;j<=n-i;j++)//画空格 
            printf(" "); 
       for(j=1;j<=i;j++) 
            printf("*");//输出前半边 
       for(j=i-1;j>=1;j--) 
            printf("*");//输出后半边 
       printf("\n");  
    } 
	return 0;
}
