#include "stdio.h" /*�ǹȲ��룺������Ȼ����������������������3�ټ�1���������ż�������������2��
���ѭ��������n�������ն��ܹ��õ�1��Ҫ��ʹ��9����Ȼ����֤�ǹȲ��룬��¼ÿ����Ȼ�����սǹȲ���õ�1�Ĳ�������
�������9����Ȼ������Ӧ�Ĳ�������9����Ȼ��Ϊm,m+1,.....m+8,���У�m�Ӽ��������롣 */
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
