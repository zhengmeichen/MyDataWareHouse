#include "stdio.h" /*角谷猜想：任意自然数如果它是奇数，则对它乘3再加1，如果它是偶数，则对它除以2，
如此循环，经过n步后，最终都能够得到1。要求使用9个自然数验证角谷猜想，记录每个自然数按照角谷猜想得到1的步骤数，
并输出这9个自然数及相应的步骤数，9个自然数为m,m+1,.....m+8,其中，m从键盘上输入。 */
#include "math.h"
int main()  
{  
    int i,m,count;  
    scanf("%d",&m);  
    for(i=m;i<m+9;i++)  
    {  
        count=0;
		printf("%d,",i);  
        int n=i;  
        while(n!=1)  
        {  
            if(n%2==0)  
            {  
                n=n/2;  
                count++;  
                //printf("%d,",n);  
                continue;  
            }  
            else   
            {  
                n=3*n+1;  
                count++;  
                //printf("%d,",n);  
                continue;  
            }  
        }  
        printf("%d\n",count);  
    }  
    return 0;   
} 
