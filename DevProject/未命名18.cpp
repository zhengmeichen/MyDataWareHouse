#include "stdio.h"  /*����һά���飬�޶����50��Ԫ�ء�
ͨ��ѭ����ֵ쳲��������е�ÿ��Ԫ�ص����顣��������m,nֵ�����m,n��Ӧ��Ԫ�غ͡�m,n��0��ʼ������ */
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
