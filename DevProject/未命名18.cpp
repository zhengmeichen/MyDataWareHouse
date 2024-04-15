#include "stdio.h"  /*定义一维数组，限定最多50个元素。
通过循环赋值斐波那契数列的每个元素到数组。键盘输入m,n值，输出m,n对应的元素和。m,n从0开始计数。 */
#include "math.h" 
int main()  
{  
    int m,n,i,sum=0;
	int a[50]={1};  
    scanf("%d%d",&m,&n);  
    for(i=0;i<50;i++)  
    {  
        if(i>1)  
        {  
            a[i]=a[i-1]+a[i-2];  
        }  
        else a[i]=1;  
    }  
    for(i=0;i<50;i++)  
    {  
        //printf("%d\n",a[i]);  
    }  
    for(i=0;i<50;i++)  
    {  
        if(i==m) sum+=a[i];  
        if(i==n) sum+=a[i];  
    }  
    printf("%d\n",sum);  
    return 0;  
 }  
