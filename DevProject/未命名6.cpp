#include "stdio.h"/*һ������Ϊ L �׵Ĳ��ϣ���Ҫ�سɳ���Ϊ a �׺� b �׵Ķ̲��ϣ�
���� L �� a �� b �Ӽ��������룬���������ֶ̲��ϸ��ض��ٸ�ʱ��ʣ��Ĳ������٣�
���a��b�ĸ������Լ�ʣ����ϵĳ��ȡ�L��a��b��Ϊ������ */
#include "math.h" 
int main()
{
	int l,a,b,c,d,e,f,g,h;
	scanf("%d%d%d",&l,&a,&b);
	h=l;
    for(c=0;c*a<=l;c++)
    {
    	for(d=0;d*b<=l;d++)
    	{
    		e=l-c*a-b*d;
			if(e<0) continue; 
			else 
			{
				if(e<h)
    		    {
    			    h=e;
    			    f=c;
    			    g=d;
			    }
			    else if(e==h) 
			    {
			    	h=e;
			    	f=c;
			    	g=d;
				}
			}
		}
	}
    printf("%d,%d,%d\n",f,g,h);
	return 0;
}
